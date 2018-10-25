#include "stdafx.h"
#include "CppUnitTest.h"

#include "BasicView.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Handmada::TetraCode;
using namespace Handmada::TetraCode::Matrix;


namespace UnitTest
{
	TEST_CLASS(MatrixViewTest)
	{
	public:

		TEST_METHOD(BasicViewFunctionalityTest)
		{
			const auto HEIGHT = coord_t(3);
			const auto WIDTH = coord_t(4);
			int expected[HEIGHT][WIDTH] = {
				{ 1, 2, 3, 4 },
				{ 5, 6, 7, 8 },
				{ 9, 0, 1, 2 }
			};
            auto values = std::vector<int>(&expected[0][0], &expected[0][0] + WIDTH * HEIGHT);

			auto view = BasicView<int>(std::move(values), WIDTH, HEIGHT);
			auto test = [&view]() { return view.get(view.width(), view.height()); };
			Assert::AreEqual(HEIGHT, view.height());
			Assert::AreEqual(WIDTH, view.width());

			for (auto x = coord_t(0); x < view.width(); x++) {
				for (auto y = coord_t(0); y < view.height(); y++) {
					Assert::AreEqual(expected[y][x], view.get(x, y));
				}
			}

			Assert::ExpectException<ViewOutOfRangeException>(test);
		}


        TEST_METHOD(BasicViewCtorFaultTest)
        {
            const auto HEIGHT = coord_t(3);
            const auto WIDTH = coord_t(4);
            auto values = std::vector<int>();  // intentionally left empty

            // Constructor's fault
            auto test = [&values, WIDTH, HEIGHT]() { return BasicView<int>(std::move(values), WIDTH, HEIGHT); };
            Assert::ExpectException<ViewSizeMismatchException>(test);
        }

	};
}