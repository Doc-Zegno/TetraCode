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
    TEST_CLASS(HDScramblerTest)
    {
    public:

        TEST_METHOD(HDScramblerEncodingTest)
        {
            byte_t bytes[] = { 0x00, 0x01, 0x02, 0x03, 0x0F };
            byte_t expected[] = { 0xAF, 0xAF, 0xFF, 0xAF, 0xFE, 0xAF, 0xFD, 0x03, 0x0F };

            auto scrambler = HighDensityScrambler();
            auto iterator = scrambler.encodingIterator(
                BasicIterator<byte_t>::create(std::begin(bytes), std::end(bytes))
            );
            auto test = [&iterator]() { return iterator->current(); };

            // Exception should be thrown if current() is called before moveNext()
            Assert::ExpectException<InvalidIteratorException>(test);

            for (auto i = 0; i < 9; i++) {
                Assert::IsTrue(iterator->moveNext());
                Assert::AreEqual(expected[i], iterator->current());
            }

            // Exception should be thrown if current() is called after last element is visited
            Assert::IsFalse(iterator->moveNext());
            Assert::ExpectException<InvalidIteratorException>(test);
        }


        TEST_METHOD(HDScramblerDecodingTest)
        {
            byte_t bytes[] = { 0xAF, 0xAF, 0xFF, 0xAF, 0xFE, 0xAF, 0xFD, 0x03, 0x0F };
            byte_t expected[] = { 0x00, 0x01, 0x02, 0x03, 0x0F };

            auto scrambler = HighDensityScrambler();
            auto iterator = scrambler.decodingIterator(
                BasicIterator<byte_t>::create(std::begin(bytes), std::end(bytes))
            );
            auto test = [&iterator]() { return iterator->current(); };

            // Exception should be thrown if current() is called before moveNext()
            Assert::ExpectException<InvalidIteratorException>(test);

            for (auto i = 0; i < 5; i++) {
                Assert::IsTrue(iterator->moveNext());
                Assert::AreEqual(expected[i], iterator->current());
            }
            
            // Exception should be thrown if current() is called after last element is visited
            Assert::IsFalse(iterator->moveNext());
            Assert::ExpectException<InvalidIteratorException>(test);
        }


        TEST_METHOD(HDScramblerPipelineTest)
        {
            byte_t bytes[] = { 0x00, 0x01, 0x02, 0x03, 0x0F };

            auto scrambler = HighDensityScrambler();
            auto iterator = scrambler.decodingIterator(
                scrambler.encodingIterator(
                    BasicIterator<byte_t>::create(std::begin(bytes), std::end(bytes))
                )
            );

            for (auto b : bytes) {
                Assert::IsTrue(iterator->moveNext());
                Assert::AreEqual(b, iterator->current());
            }
            Assert::IsFalse(iterator->moveNext());
        }

    };
}