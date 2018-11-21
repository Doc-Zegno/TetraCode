#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <tuple>

#include <cstring>

#include "Types.h"
#include "Format.h"

#include "Pixel.h"
#include "HsvPalette.h"

#include "ScramblingPipeline.h"
#include "PreambleScrambler.h"
#include "ParityCheckScrambler.h"
#include "HighDensityScrambler.h"

#include "ColorToPixelConverter.h"
#include "IntegerScalingConverter.h"

#include "Encoder.h"
#include "Decoder.h"

#include "Reader.h"
#include "Writer.h"
#include "InputFileStream.h"
#include "OutputFileStream.h"

#include "Image.h"

#include "BasicTraceableException.h"
#include "BasicTraceableExceptionMacros.h"

using namespace Handmada::TetraCode;


static bool isTextFile(const char* fileName)
{
    auto p = std::strchr(fileName, '.');
    if (!p) {
        throw Exception::BasicTraceableException(
            Format::str("filename \"{}\" doesn't have an extension", fileName)
        );
    }
    return std::strcmp(p + 1, "txt") == 0;
}


static std::tuple<bool, std::string, std::string> parseArgs(int argc, char* argv[])
{
    if (argc < 3) {
        throw Exception::BasicTraceableException(
            "too few arguments: expected paths to both input and output files"
        );
    }

    auto fromFileName = argv[1];
    auto toFileName = argv[2];

    if (isTextFile(fromFileName)) {
        // First file is a text => encoding
        if (isTextFile(toFileName)) {
            throw Exception::BasicTraceableException(
                "at least one file should be an image one"
            );
        }
        return std::make_tuple(true, fromFileName, toFileName);
    } else {
        // First file is an image => decoding
        if (!isTextFile(toFileName)) {
            throw Exception::BasicTraceableException(
                "at least one file should be a text one"
            );
        }
        return std::make_tuple(false, fromFileName, toFileName);
    }
}


static void encode(
    const std::string& fromFileName,
    const std::string& toFileName,
    Sequence::Scrambler& scrambler,
    coord_t maxSide,
    coord_t minSide,
    coord_t scaleFactor,
    const Visual::HsvPalette& palette
)
{
    // Get byte sequence
    std::cout << "Reading byte stream from input file...\n";
    auto stream = IO::InputFileStream(fromFileName);
    auto sequence = Sequence::readSequence(stream);

    // Encode sequence
    std::cout << "Encoding...\n";
    sequence = scrambler.encodingIterator(std::move(sequence));
    auto view = Code::sequence2image(*sequence, maxSide, minSide);

    // Convert to image
    auto paletteConverter = Matrix::ColorToPixelConverter(palette);
    auto scaleConverter = Matrix::IntegerScalingConverter(scaleFactor);
    auto image = scaleConverter.directView(
        paletteConverter.directView(std::move(view))
    );

    // Save image
    std::cout << "Saving image to file...\n";
    Image::exportImage(*image, toFileName);
}


static void decode(
    const std::string& fromFileName,
    const std::string& toFileName,
    Sequence::Scrambler& scrambler,
    Sequence::PreambleScrambler& preambleScrambler,
    const Version& hostVersion,
    coord_t scaleFactor,
    const Visual::HsvPalette& palette
)
{
    // Get image from file
    std::cout << "Loading image from file...\n";
    auto image = Image::importImage(fromFileName);

    // Convert pixel image to color view
    auto paletteConverter = Matrix::ColorToPixelConverter(palette);
    auto scaleConverter = Matrix::IntegerScalingConverter(scaleFactor);
    auto view = paletteConverter.inverseView(
        scaleConverter.inverseView(std::move(image))
    );

    // Decode view to sequence
    std::cout << "Decoding...\n";
    auto sequence = Code::image2sequence(*view);
    sequence = scrambler.decodingIterator(std::move(sequence));

    // Check guest version
    auto guestVersion = preambleScrambler.guestVersion();
    if (hostVersion == guestVersion) {
        std::cout << "OK, guest version (" << guestVersion.toString()
            << ") is compatible with the host one\n";
    } else {
        std::cout << "<!> Warning: guest version (" << guestVersion.toString()
            << ") is not compatible with the host one\n";
        std::cout << "<!> Warning: decoded sequence can be different from the original one\n";
    }

    // Store into file
    std::cout << "Saving byte stream to file...\n";
    auto stream = IO::OutputFileStream(toFileName);
    Sequence::writeSequence(*sequence, stream);
}


int main(int argc, char* argv[])
{
    try {
        const coord_t MAX_SIDE = 2048;
        const coord_t MIN_SIDE = 64;
        const coord_t SCALE_FACTOR = 4;

        const auto GROUP_SIZE = 7;  // for parity check
        const auto PADDING = 4;  // for high density

        // Parse args
        auto [isEncoding, fromFileName, toFileName] = parseArgs(argc, argv);

        // Define palette
        Visual::Pixel basePixels[2][2] = {
            { "#ff4000", "#ffc000" },
            { "#c00040", "#600080" },
        };
        auto palette = Visual::HsvPalette(basePixels);

        // Define host version
        auto hostVersion = Version(0, 1, 0);
        std::cout << "TetraCode v" << hostVersion.toString() << std::endl;

        // Define scrambling pipeline
        auto scramblers = std::vector<std::unique_ptr<Sequence::Scrambler>>();
        scramblers.push_back(Sequence::PreambleScrambler::create(hostVersion));
        scramblers.push_back(Sequence::ParityCheckScrambler::create(GROUP_SIZE));
        scramblers.push_back(Sequence::HighDensityScrambler::create(PADDING));
        auto pipeline = Sequence::ScramblingPipeline(scramblers);

        // Dispatch
        if (isEncoding) {
            encode(fromFileName, toFileName, pipeline, MAX_SIDE, MIN_SIDE, SCALE_FACTOR, palette);
        } else {
            auto& preambleScrambler = dynamic_cast<Sequence::PreambleScrambler&>(*scramblers[0]);
            decode(fromFileName, toFileName, pipeline, preambleScrambler, 
                hostVersion, SCALE_FACTOR, palette);
        }

        // OK
        std::cout << "Done\n";

    } catch (Exception::TraceableException& e) {
        auto trace = e.buildTraceString();
        std::cerr << "Aborted:\n" << trace << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Aborted with untraceable exception:\n" << e.what() << std::endl;
    }
}