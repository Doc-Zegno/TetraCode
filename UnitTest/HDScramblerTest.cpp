#include "stdafx.h"
#include "CppUnitTest.h"

#include "HighDensityScrambler.h"
#include "BasicIterator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Handmada::TetraCode;
using namespace Handmada::TetraCode::Iterator;
using namespace Handmada::TetraCode::Scrambler;


namespace UnitTest
{
    TEST_CLASS(HDScramblerTest)
    {
    public:

        TEST_METHOD(EncodingIteratorTest)
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

            for (auto e : expected) {
                Assert::IsTrue(iterator->moveNext());
                Assert::AreEqual(e, iterator->current());
            }

            // Exception should be thrown if current() is called after last element is visited
            Assert::IsFalse(iterator->moveNext());
            Assert::ExpectException<InvalidIteratorException>(test);
        }


        TEST_METHOD(DecodingIteratorTest)
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

            for (auto e : expected) {
                Assert::IsTrue(iterator->moveNext());
                Assert::AreEqual(e, iterator->current());
            }
            
            // Exception should be thrown if current() is called after last element is visited
            Assert::IsFalse(iterator->moveNext());
            Assert::ExpectException<InvalidIteratorException>(test);
        }


        TEST_METHOD(DecodingIteratorCtorFaultTest)
        {
            auto value = byte_t(0x00);
            auto scrambler = HighDensityScrambler();
            auto test = [&scrambler, &value]() {
                return scrambler.decodingIterator(
                    BasicIterator<byte_t>::create(&value, &value)
                );
            };

            // Constructor's fault
            Assert::ExpectException<CorruptedInputSequenceException>(test);
        }


        TEST_METHOD(DecodingIteratorMoveNextFaultTest)
        {
            byte_t bytes[] = { 0xAF, 0xAF };
            auto scrambler = HighDensityScrambler();
            auto iterator = scrambler.decodingIterator(
                BasicIterator<byte_t>::create(std::begin(bytes), std::end(bytes))
            );
            auto test = [&iterator]() { return iterator->moveNext(); };

            // moveNext()'s fault
            Assert::ExpectException<CorruptedInputSequenceException>(test);
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