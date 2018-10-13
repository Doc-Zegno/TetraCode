#include "stdafx.h"
#include "CppUnitTest.h"

#include "BasicIterator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TetraCode::Iterator;


namespace UnitTest
{		
    TEST_CLASS(IteratorTest)
    {
    public:
        
        TEST_METHOD(BasicIteratorFunctionalityTest)
        {
            int values[] = { 1, 2, 3, 4, 5 };
            auto iterator = BasicIterator<int>(std::begin(values), std::end(values));

            for (auto v : values) {
                auto hasNext = iterator.moveNext();
                Assert::IsTrue(hasNext);
                auto current = iterator.current();
                Assert::AreEqual(v, current);
            }

            Assert::IsFalse(iterator.moveNext());
        }


        TEST_METHOD(BasicIteratorEmptyArrayTest)
        {
            auto value = 0;
            auto iterator = BasicIterator<int>(&value, &value);
            Assert::IsFalse(iterator.moveNext());
        }

    };
}