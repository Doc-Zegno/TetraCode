#include "Image.h"

#include "atlimage.h"

#include <cstdint>
#include <iostream>
#include <string>


namespace Handmada::TetraCode::Image {
    using Visual::Pixel;
    using Matrix::MatrixView;


    void exportImage(const MatrixView<Pixel>& view, const std::string& fileName)
    {
        auto width = view.width();
        auto height = view.height();

        CImage image;
        image.Create(width, height, 24);
        auto imageBuffer = (byte_t*) image.GetBits();

        auto pitch = image.GetPitch();
        if (pitch < 0) {
            imageBuffer += pitch * (height - 1);
            pitch = -pitch;
        }

        auto imageDisplacement = 0;
        for (auto y = coord_t(0); y < height; y++) {
            for (auto x = coord_t(0); x < width; x++) {
                auto pixel = view.get(x, y);
                auto index = imageDisplacement + x * 3;

                imageBuffer[index] = pixel.b();
                imageBuffer[index + 1] = pixel.g();
                imageBuffer[index + 2] = pixel.r();
            }
            imageDisplacement += pitch;
        }

        image.Save(fileName.c_str());
        image.Destroy();
    }


    std::pair<std::unique_ptr<Pixel[]>, int> ImportImageFromFile(const char* path, bool isVerbose)
    {
        CImage image;
        auto result = image.Load(path);
        if (result != S_OK) {
            throw std::runtime_error(std::string("Unable to load image \"") + path + "\"\n");
        }

        auto side = image.GetHeight();
        auto pixels = new Pixel[side * side];

        auto imageBuffer = (byte_t*) image.GetBits();
        auto pitch = image.GetPitch();
        if (pitch < 0) {
            imageBuffer += pitch * (side - 1);
            pitch = -pitch;
        }

        auto imageDisplacement = 0;
        for (auto i = 0; i < side; i++) {
            for (auto j = 0; j < side; j++) {
                auto index = imageDisplacement + j * 3;
                auto& pixel = pixels[i * side + j];
                pixel = Pixel(imageBuffer[index + 2], imageBuffer[index + 1], imageBuffer[index]);
            }
            imageDisplacement += pitch;
        }

        if (isVerbose) {
            std::cout << "Successfully loaded image: \"" << path << "\"\n";
        }
        image.Destroy();
        return std::make_pair(std::unique_ptr<Pixel[]>(pixels), side);
    }
}
