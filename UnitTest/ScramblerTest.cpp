#include "stdafx.h"
#include "CppUnitTest.h"

#include "HighDensityScrambler.h"
#include "BasicIterator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TetraCode;
using namespace TetraCode::Iterator;
using namespace TetraCode::Scrambler;


namespace UnitTest
{
    TEST_CLASS(ScramblerTest)
    {
    public:

        TEST_METHOD(HighDensityScramblerEncodingTest)
        {
            byte_t bytes[] = { 0x00, 0x01, 0x02, 0x03, 0x0F };
            byte_t expected[] = { 0xAF, 0xAF, 0xFF, 0xAF, 0xFE, 0xAF, 0xFD, 0x03, 0x0F };

            auto scrambler = HighDensityScrambler();
            auto iterator = scrambler.encodingIterator(
                BasicIterator<byte_t>::create(std::begin(bytes), std::end(bytes))
            );

            for (auto i = 0; i < 9; i++) {
                Assert::IsTrue(iterator->moveNext());
                Assert::AreEqual(expected[i], iterator->current());
            }
            Assert::IsFalse(iterator->moveNext());
        }

    };
}