#include "stdafx.h"
#include "CppUnitTest.h"

#include <vector>

#include "ColorToPixelConverter.h"
#include "BasicView.h"
#include "HsvPalette.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Handmada::TetraCode;
using namespace Handmada::TetraCode::Matrix;
using namespace Handmada::TetraCode::Visual;


namespace UnitTest
{
    TEST_CLASS(ColorToPixelConverterTest)
    {
    public:

        TEST_METHOD(DirectViewTest)
        {
            const auto HEIGHT = coord_t(3);
            const auto WIDTH = coord_t(4);
            Pixel pixels[HEIGHT][WIDTH] = { };
            Pixel basePixels[][2] = {
                { { 255, 0, 0 }, { 0, 0, 255 } },
                { { 0, 255, 0 }, { 255, 255, 0 } }
            };
            auto palette = HsvPalette(basePixels);
            auto values = std::vector<Color>();

            for (auto i = coord_t(0); i < HEIGHT; i++) {
                for (auto j = coord_t(0); j < WIDTH; j++) {
                    auto color = Color(true, i % 2, j % 2, (i + j) % 2);
                    pixels[i][j] = palette.color2pixel(color);
                    values.push_back(color);
                }
            }

            auto converter = ColorToPixelConverter(palette);
            auto view = converter.directView(BasicView<Color>::create(std::move(values), WIDTH, HEIGHT));

            Assert::AreEqual(view->height(), HEIGHT);
            Assert::AreEqual(view->width(), WIDTH);
            for (auto x = coord_t(0); x < view->width(); x++) {
                for (auto y = coord_t(0); y < view->height(); y++) {
                    Assert::AreEqual(pixels[y][x].toString(), view->get(x, y).toString());
                }
            }

            auto test = [&view]() { return view->get(view->width(), view->height()); };
            Assert::ExpectException<ViewOutOfRangeException>(test);
        }


        TEST_METHOD(InverseViewTest)
        {
            const auto HEIGHT = coord_t(3);
            const auto WIDTH = coord_t(4);
            Color colors[HEIGHT][WIDTH] = { };
            Pixel basePixels[][2] = {
                { { 255, 0, 0 }, { 0, 0, 255 } },
                { { 0, 255, 0 }, { 255, 255, 0 } }
            };
            auto palette = HsvPalette(basePixels);
            auto values = std::vector<Pixel>();

            for (auto i = coord_t(0); i < HEIGHT; i++) {
                for (auto j = coord_t(0); j < WIDTH; j++) {
                    auto color = Color(true, i % 2, j % 2, (i + j) % 2);
                    auto pixel = palette.color2pixel(color);
                    colors[i][j] = color;
                    values.push_back(pixel);
                }
            }

            auto converter = ColorToPixelConverter(palette);
            auto view = converter.inverseView(BasicView<Pixel>::create(std::move(values), WIDTH, HEIGHT));

            Assert::AreEqual(view->height(), HEIGHT);
            Assert::AreEqual(view->width(), WIDTH);
            for (auto x = coord_t(0); x < view->width(); x++) {
                for (auto y = coord_t(0); y < view->height(); y++) {
                    Assert::IsTrue(colors[y][x] == view->get(x, y));
                }
            }

            auto test = [&view]() { return view->get(view->width(), view->height()); };
            Assert::ExpectException<ViewOutOfRangeException>(test);
        }

    };
}