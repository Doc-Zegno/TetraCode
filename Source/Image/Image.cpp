#include "Image.h"

#include <vector>

#include "lodepng.h"

#include "Format.h"
#include "BasicView.h"
#include "BasicTraceableException.h"
#include "BasicTraceableExceptionMacros.h"


namespace Handmada::TetraCode::Image {
    using Visual::Pixel;
    using Matrix::MatrixView;


    void exportImage(const MatrixView<Pixel>& view, const std::string& fileName)
    {
        auto width = view.width();
        auto height = view.height();

        // Raw bytes
        auto image = std::vector<byte_t>(width * height * 4, 0xFF);
        for (auto x = coord_t(0); x < width; x++) {
            for (auto y = coord_t(0); y < height; y++) {
                auto base = (y * width + x) * 4;  // RGBA => 4 bytes
                auto pixel = view.get(x, y);
                for (auto c = 0; c < 3; c++) {
                    image[base + c] = pixel[c];
                }
            }
        }

        // Encode the image
        unsigned error = lodepng::encode(fileName.c_str(), image, width, height);

        // If there's an error, throw it
        if (error) {
            throw Exception::BasicTraceableException(
                Format::str("encoder error {}: {}", error, lodepng_error_text(error))
            );
        }
    }


    std::unique_ptr<MatrixView<Pixel>> importImage(const std::string& fileName)
    {
        std::vector<unsigned char> image;  // The raw pixels
        unsigned width, height;

        // Decode
        unsigned error = lodepng::decode(image, width, height, fileName.c_str());

        // If there's an error, throw it
        if (error) {
            throw Exception::BasicTraceableException(
                Format::str("decoder error {}: {}", error, lodepng_error_text(error))
            );
        }

        auto pixels = std::vector<Pixel>(width * height, Pixel());

        for (auto x = 0U; x < width; x++) {
            for (auto y = 0U; y < height; y++) {
                auto base = y * width + x;
                auto imageBase = base * 4;  // RGBA => 4 bytes

                byte_t channels[3];
                for (auto c = 0; c < 3; c++) {
                    channels[c] = image[imageBase + c];
                }

                pixels[base] = Pixel(channels[0], channels[1], channels[2]);
            }
        }

        return std::unique_ptr<MatrixView<Pixel>>(
            new Matrix::BasicView<Pixel>(std::move(pixels), width, height)
        );
    }
}
