#include "stdafx.h"
#include "CppUnitTest.h"

#include <vector>

#include "IntegerScalingConverter.h"
#include "BasicView.h"
#include "HsvPalette.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Handmada::TetraCode;
using namespace Handmada::TetraCode::Matrix;
using namespace Handmada::TetraCode::Visual;


namespace UnitTest
{
    TEST_CLASS(IntegerScalingConverterTest)
    {
    public:

        TEST_METHOD(DirectViewTest)
        {
            const auto WIDTH = coord_t(3);
            const auto HEIGHT = coord_t(2);
            const auto RATIO = 2;

            Pixel image[HEIGHT][WIDTH] = {
                { "#ff0000", "#00ff00", "#0000ff", },
                { "#880000", "#008800", "#000088", },
            };
            Pixel expected[HEIGHT * RATIO][WIDTH * RATIO] = {
                { "#ff0000", "#ff0000", "#00ff00", "#00ff00", "#0000ff", "#0000ff", },
                { "#ff0000", "#ff0000", "#00ff00", "#00ff00", "#0000ff", "#0000ff", },
                { "#880000", "#880000", "#008800", "#008800", "#000088", "#000088", },
                { "#880000", "#880000", "#008800", "#008800", "#000088", "#000088", },
            };

            auto data = std::vector<Pixel>(&image[0][0], &image[0][0] + WIDTH * HEIGHT);
            auto converter = IntegerScalingConverter(RATIO);
            auto view = converter.directView(
                BasicView<Pixel>::create(std::move(data), WIDTH, HEIGHT)
            );

            Assert::AreEqual(WIDTH * RATIO, view->width());
            Assert::AreEqual(HEIGHT * RATIO, view->height());
            for (auto x = coord_t(0); x < view->width(); x++) {
                for (auto y = coord_t(0); y < view->height(); y++) {
                    Assert::IsTrue(expected[y][x] == view->get(x, y));
                }
            }

            auto test = [&view]() { return view->get(view->width(), view->height()); };
            Assert::ExpectException<ViewOutOfRangeException>(test);
        }


        TEST_METHOD(InverseViewTest)
        {
            const auto WIDTH = coord_t(6);
            const auto HEIGHT = coord_t(4);
            const auto RATIO = 2;

            Pixel expected[HEIGHT / RATIO][WIDTH / RATIO] = {
                { "#f80000", "#00f800", "#0000f8", },
                { "#880000", "#008800", "#000088", },
            };

            // Note that converter must average pixels within region RATIOxRATIO
            Pixel image[HEIGHT][WIDTH] = {
                { "#f60000", "#f90000", "#00fa00", "#00f700", "#0000f9", "#0000f7", },
                { "#f70000", "#fa0000", "#00f900", "#00f600", "#0000f9", "#0000f7", },
                { "#880000", "#880000", "#008000", "#008900", "#000084", "#00008a", },
                { "#880000", "#880000", "#008700", "#009000", "#000086", "#00008c", },
            };

            auto data = std::vector<Pixel>(&image[0][0], &image[0][0] + WIDTH * HEIGHT);
            auto converter = IntegerScalingConverter(RATIO);
            auto view = converter.inverseView(
                BasicView<Pixel>::create(std::move(data), WIDTH, HEIGHT)
            );

            Assert::AreEqual(WIDTH / RATIO, view->width());
            Assert::AreEqual(HEIGHT / RATIO, view->height());
            for (auto x = coord_t(0); x < view->width(); x++) {
                for (auto y = coord_t(0); y < view->height(); y++) {
                    Assert::IsTrue(expected[y][x] == view->get(x, y));
                }
            }

            auto test = [&view]() { return view->get(view->width(), view->height()); };
            Assert::ExpectException<ViewOutOfRangeException>(test);
        }


        TEST_METHOD(InverseViewCtorFaultTest)
        {
            const auto WIDTH = coord_t(6);
            const auto HEIGHT = coord_t(4);
            const auto RATIO = 3;  // Note: 4 % 3 != 0
            
            Pixel image[HEIGHT][WIDTH] = {
                { "#f60000", "#f90000", "#00fa00", "#00f700", "#0000f9", "#0000f7", },
                { "#f70000", "#fa0000", "#00f900", "#00f600", "#0000f9", "#0000f7", },
                { "#880000", "#880000", "#008000", "#008900", "#000084", "#00008a", },
                { "#880000", "#880000", "#008700", "#009000", "#000086", "#00008c", },
            };

            auto data = std::vector<Pixel>(&image[0][0], &image[0][0] + WIDTH * HEIGHT);
            auto converter = IntegerScalingConverter(RATIO);

            // Constructor's fault: bad scaling ratio
            auto test = [&converter, &data, WIDTH, HEIGHT]() {
                return converter.inverseView(
                    BasicView<Pixel>::create(std::move(data), WIDTH, HEIGHT)
                );
            };

            Assert::ExpectException<ViewBadRatioException>(test);
        }

    };
}