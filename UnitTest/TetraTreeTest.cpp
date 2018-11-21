#include "stdafx.h"
#include "CppUnitTest.h"

#include "TetraTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Handmada::TetraCode;
using namespace Handmada::TetraCode::Code;


namespace UnitTest
{
    TEST_CLASS(TetraTreeTest)
    {
    public:

        TEST_METHOD(SpawnChildrenTest)
        {
            const auto SIDE = coord_t(256);
            const auto ODDITY = 0;
            auto tree = TetraTree(0, 0, SIDE, 0, 0, ODDITY);

            // No children at start
            Assert::AreEqual(0U, tree.children().size());

            // Spawn them
            tree.spawnChildren();
            Assert::AreEqual(4U, tree.children().size());

            // Check children's properties
            // TetraTree MUST use the following order of children traversing
            coord_t indices[4][2] = {
                { 0, 0 },
                { 0, 1 },
                { 1, 1 },
                { 1, 0 },
            };

            for (auto i = 0; i < 4; i++) {
                auto& child = tree.children()[i];

                // Non-initialized children must be inactive
                Assert::IsFalse(child->color().isActive());

                // Check size
                auto halfSide = SIDE / 2;
                Assert::AreEqual(halfSide, child->side());

                // Check oddity
                Assert::AreEqual(1 - ODDITY, child->oddity());

                // Check xMin and yMin
                auto xMin = halfSide * indices[i][1];
                auto yMin = halfSide * indices[i][0];
                Assert::AreEqual(xMin, child->xMin());
                Assert::AreEqual(yMin, child->yMin());

                // Check pivot
                auto xPivot = 1 - indices[i][1];
                auto yPivot = 1 - indices[i][0];
                Assert::AreEqual(xPivot, child->xPivot());
                Assert::AreEqual(yPivot, child->yPivot());
            }
        }


        TEST_METHOD(RemoveChildrenTest)
        {
            auto tree = TetraTree(0, 0, 0, 0, 0, 0);

            // 0 children at start
            Assert::AreEqual(0U, tree.children().size());
            
            // 4 children after spawn
            tree.spawnChildren();
            Assert::AreEqual(4U, tree.children().size());

            // 0 after removal
            tree.removeChildren();
            Assert::AreEqual(0U, tree.children().size());
        }


        TEST_METHOD(CalculateChildrenColorsTest)
        {
            const auto ODDITY = 0;
            auto tree = TetraTree(0, 0, 0, 0, 0, ODDITY);
            tree.spawnChildren();
            
            // Codebits
            bool isActives[] = { true, true, false, false };
            auto colorNumber = 1;
            auto brightnessLevel = 1;
            auto bits = CodeBits(isActives, colorNumber, brightnessLevel);

            // Assign colors and check
            tree.calculateChildrenColors(bits);
            for (auto i = 0; i < 4; i++) {
                auto& child = tree.children()[i];
                auto color = child->color();
                auto number = isActives[i] ? colorNumber : 1 - colorNumber;
                auto huePair = 1 - ODDITY;
                Assert::AreEqual(isActives[i], color.isActive());
                Assert::AreEqual(number, color.number());
                Assert::AreEqual(brightnessLevel, color.brightnessLevel());
                Assert::AreEqual(huePair, color.huePair());
            }
        }


        TEST_METHOD(CalculateHeightTest)
        {
            auto tree = TetraTree(0, 0, 0, 0, 0, 0);
            
            // Tree without children should have zero height
            Assert::AreEqual(0, tree.calculateHeight());

            // Now it should have height of 1
            tree.spawnChildren();
            Assert::AreEqual(1, tree.calculateHeight());

            // Now - 2
            tree.children()[2]->spawnChildren();
            Assert::AreEqual(2, tree.calculateHeight());
        }

    };
}