#include "HsvPalette.h"

#include <cmath>
#include <algorithm>


namespace Handmada::TetraCode::Visual {
    HsvPalette::HsvPalette(const Pixel (&basePixels)[2][2])
    {
        for (auto i = 0; i < 2; i++) {
            for (auto j = 0; j < 2; j++) {
                auto& base = basePixels[i][j];
                auto dR = (255U - base.r()) / 16U;
                auto dG = (255U - base.g()) / 16U;
                auto dB = (255U - base.b()) / 16U;

                _pixels[i][j][0] = base;
                for (auto level = 1; level < 16; level++) {
                    auto& pixel = _pixels[i][j][level];
                    auto r = base.r() + dR * level;
                    auto g = base.g() + dG * level;
                    auto b = base.b() + dB * level;
                    pixel = Pixel(r, g, b);
                }
            }
        }
    }


    Pixel HsvPalette::color2pixel(Color color) const
    {
        auto pair = color.huePair();
        auto number = color.number();
        auto shift = color.isActive() ? 0 : 8;
        auto level = color.brightnessLevel() + shift;
        return _pixels[pair][number][level];
    }


    Color HsvPalette::pixel2color(Pixel pixel) const
    {
        return pixel2colorRobust(pixel);
    }


    Color HsvPalette::pixel2colorRobust(Pixel pixel) const
    {
        auto bestHuePair = 0;
        auto bestColorNumber = 0;
        auto bestLevel = 0;
        auto bestDistance = 3 * (255 * 255);

        for (auto i = 0; i < 2; i++) {
            for (auto j = 0; j < 2; j++) {
                for (auto k = 0; k < 16; k++) {
                    auto match = _pixels[i][j][k];
                    auto dR = match.r() - pixel.r();
                    auto dG = match.g() - pixel.g();
                    auto dB = match.b() - pixel.b();
                    auto distance = dR * dR + dG * dG + dB * dB;

                    if (distance < bestDistance) {
                        bestHuePair = i;
                        bestColorNumber = j;
                        bestLevel = k;
                        bestDistance = distance;
                    }
                }
            }
        }

        return Color(bestLevel < 8, bestHuePair, bestLevel, bestColorNumber);
    }


    // TODO: make more robust
    Color HsvPalette::pixel2colorFast(Pixel pixel) const
    {
        auto bestHuePair = 0;
        auto bestColorNumber = 0;
        auto bestDistance = 3 * (255 * 255);
        Pixel bestMatch;

        for (auto i = 0; i < 2; i++) {
            for (auto j = 0; j < 2; j++) {
                auto match = _pixels[i][j][0];
                auto dR = match.r() - pixel.r();
                auto dG = match.g() - pixel.g();
                auto dB = match.b() - pixel.b();
                auto distance = dR * dR + dG * dG + dB * dB;

                if (distance < bestDistance) {
                    bestHuePair = i;
                    bestColorNumber = j;
                    bestDistance = distance;
                    bestMatch = match;
                }
            }
        }

        auto dR = (255U - bestMatch.r()) / 16U;
        auto dG = (255U - bestMatch.g()) / 16U;
        auto dB = (255U - bestMatch.b()) / 16U;
        auto levelR = std::lround((float(pixel.r() - bestMatch.r())) / dR);
        auto levelG = std::lround((float(pixel.g() - bestMatch.g())) / dG);
        auto levelB = std::lround((float(pixel.b() - bestMatch.b())) / dB);
        auto level = std::max(levelR, std::max(levelG, levelB));

        return Color(level < 8, bestHuePair, level, bestColorNumber);
    }
}
