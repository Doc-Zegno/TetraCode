#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdexcept>

#include "HsvPalette.h"
#include "Encoder.h"
#include "Decoder.h"
#include "Image.h"

using namespace TetraCode;


std::pair<std::unique_ptr<byte_t[]>, int> scrambleWithDummy(const byte_t* sequence, int length)
{
    const byte_t ZERO_BITS_DUMMY = 0b10101111;
    const int PADDING = 5;

    auto scrambled = new byte_t[length * 2 + PADDING];

    for (auto i = 0; i < PADDING; i++) {
        scrambled[i] = ~0U;
    }

    auto p = scrambled + PADDING;
    auto q = sequence;
    while (q < sequence + length) {
        auto next = *q;
        q++;
        
        auto activeMask = next & 0b00001111;
        if (activeMask == 0 || (activeMask & (activeMask - 1)) == 0 || next == ZERO_BITS_DUMMY) {
            *p = ZERO_BITS_DUMMY;
            p++;
            next = ~next;
        }

        *p = next;
        p++;
    }
    return std::make_pair(std::unique_ptr<byte_t[]>(scrambled), int(p - scrambled));
}


std::pair<std::unique_ptr<byte_t[]>, int> unscrambleFromDummy(const byte_t* sequence, int length)
{
    const byte_t ZERO_BITS_DUMMY = 0b10101111;
    const int PADDING = 5;

    auto unscrambled = new byte_t[length + 1];
    auto p = unscrambled;
    auto q = sequence + PADDING;
    while (q < sequence + length) {
        auto next = *q;
        q++;

        if (next == ZERO_BITS_DUMMY) {
            next = ~(*q);
            q++;
        }

        *p = next;
        p++;
    }
    *p = '\0';
    p++;

    std::cout << "before unscrambling: " << length << std::endl;
    std::cout << "after unscrambling: " << int(p - unscrambled) << std::endl;

    return std::make_pair(std::unique_ptr<byte_t[]>(unscrambled), int(p - unscrambled));
}


void encode(const char* filePath, coord_t maxSide, coord_t minSide, coord_t pivotSide, const Palette& palette)
{
    const size_t BUFFER_SIZE = 4096;
    char buffer[BUFFER_SIZE] = { 0 };
    std::cin.read(buffer, BUFFER_SIZE - 1);
    auto length = std::strlen(buffer);

    auto scrambled = scrambleWithDummy(reinterpret_cast<byte_t*>(buffer), length);

    auto encoder = Encoder(maxSide, minSide, pivotSide, &palette);
    auto image = encoder.sequence2image(scrambled.first.get(), scrambled.second);
    ExportBufferAsImage(image.first.get(), image.second, image.second, filePath);

    std::cout << "original length = " << length << std::endl;
    std::cout << "new length = " << scrambled.second << std::endl;
    std::cout << "optimal side = " << image.second << std::endl;
    std::cout << "done\n";
}


void decode(const char* filePath, coord_t maxSide, coord_t minSide, coord_t pivotSide, const Palette& palette)
{
    auto image = ImportImageFromFile(filePath, true);
    auto decoder = Decoder(&palette);
    auto sequence = decoder.image2sequence(image.first.get(), image.second, pivotSide);
    auto unscrambled = unscrambleFromDummy(sequence.first.get(), sequence.second);
    std::cout << "Text [" << unscrambled.second << " characters total]:\n\t";
    std::cout.write(reinterpret_cast<const char*>(unscrambled.first.get()), unscrambled.second);
}


int main(int argc, char* argv[])
{
    try {
        const coord_t MAX_SIDE = 2048;
        const coord_t MIN_SIDE = 256;
        const coord_t PIVOT_SIDE = 4;


        if (argc < 2) {
            throw std::runtime_error("image export path was not specified");
        }

        bool isEncoding = true;
        if (argc >= 3) {
            if (!std::strcmp(argv[2], "-d")) {
                isEncoding = false;
            } else {
                throw std::runtime_error("unknown option [only valid is -d]");
            }
        }

        Pixel basePixels[2][2] = {
            { Pixel(255, 64, 0), Pixel(255, 192, 0) },
        { Pixel(192, 0, 64), Pixel(96, 0, 128) },
        };
        auto palette = HsvPalette(basePixels);

        if (isEncoding) {
            encode(argv[1], MAX_SIDE, MIN_SIDE, PIVOT_SIDE, palette);
        } else {
            decode(argv[1], MAX_SIDE, MIN_SIDE, PIVOT_SIDE, palette);
        }
    } catch (std::exception& e) {
        std::cerr << "Aborted with exception: " << e.what() << std::endl;
    }
}