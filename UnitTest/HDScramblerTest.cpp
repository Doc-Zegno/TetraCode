#include "stdafx.h"
#include "CppUnitTest.h"

#include "HighDensityScrambler.h"
#include "BasicIterator.h"
#include "CodeBits.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Handmada::TetraCode;
using namespace Handmada::TetraCode::Code;
using namespace Handmada::TetraCode::Sequence;


namespace UnitTest
{
    TEST_CLASS(HDScramblerTest)
    {
    public:

        TEST_METHOD(EncodingIteratorTest)
        {
            byte_t bytes[] = { 0x00, 0x01, 0x02, 0x03, 0x0F };
            byte_t expected[] = { 0x0F, 0xAF, 0xFF, 0xAF, 0xFE, 0xAF, 0xFD, 0x03, 0x0F };

            auto scrambler = HighDensityScrambler(0);
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


        TEST_METHOD(EncodingIteratorPaddingTest)
        {
            byte_t bytes[] = { 0x00, 0x01, 0x02, 0x03, 0x0F };
            // Note: first 2 bytes are padding ones
            // Note: packed values are decremented at each step
            byte_t expected[] = { 0x2F, 0x1F, 0x0F, 0xAF, 0xFF, 0xAF, 0xFE, 0xAF, 0xFD, 0x03, 0x0F };

            // Note: padding = 2
            auto scrambler = HighDensityScrambler(2);
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


        TEST_METHOD(EncodingIteratorCtorFaultTest)
        {
            byte_t bytes[] = { 0x00, 0x01, 0x02, 0x03, 0x0F };

            // Note: requested padding is too large
            auto scrambler = HighDensityScrambler(Code::CodeBits::maxSmallInt() + 1);
            auto test = [&scrambler, &bytes]() {
                return scrambler.encodingIterator(
                    BasicIterator<byte_t>::create(std::begin(bytes), std::end(bytes))
                );
            };

            // Constructor's fault
            Assert::ExpectException<TooLargePaddingException>(test);
        }


        TEST_METHOD(DecodingIteratorTest)
        {
            byte_t bytes[] = { 0x0F, 0xAF, 0xFF, 0xAF, 0xFE, 0xAF, 0xFD, 0x03, 0x0F };
            byte_t expected[] = { 0x00, 0x01, 0x02, 0x03, 0x0F };

            auto scrambler = HighDensityScrambler(0);
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


        TEST_METHOD(DecodingIteratorPaddingTest)
        {
            // Note: first 2 bytes are padding ones
            byte_t bytes[] = { 0x2F, 0x1F, 0x0F, 0xAF, 0xFF, 0xAF, 0xFE, 0xAF, 0xFD, 0x03, 0x0F };
            byte_t expected[] = { 0x00, 0x01, 0x02, 0x03, 0x0F };

            // Note: should work even if scrambler is constructed with zero padding
            auto scrambler = HighDensityScrambler(0);
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
            auto scrambler = HighDensityScrambler(0);

            // Note: empty input sequence
            auto test1 = [&scrambler, &value]() {
                return scrambler.decodingIterator(
                    BasicIterator<byte_t>::create(&value, &value)
                );
            };
            Assert::ExpectException<CorruptedInputSequenceException>(test1);

            // Note: no padding (i.e. first byte is not a packed one)
            auto test2 = [&scrambler]() {
                byte_t bytes[] = { 0x00, 0x01, 0x02 };
                scrambler.decodingIterator(
                    BasicIterator<byte_t>::create(std::begin(bytes), std::end(bytes))
                );
            };
            Assert::ExpectException<CorruptedInputSequenceException>(test2);

            // Note: inconsistent padding (second packed value is not decremented)
            auto test3 = [&scrambler]() {
                byte_t bytes[] = { 0x1F, 0x1F, 0x01, 0x02 };
                scrambler.decodingIterator(
                    BasicIterator<byte_t>::create(std::begin(bytes), std::end(bytes))
                );
            };
            Assert::ExpectException<CorruptedInputSequenceException>(test3);
        }


        TEST_METHOD(DecodingIteratorMoveNextFaultTest)
        {
            byte_t bytes[] = { 0x0F, 0xAF };
            auto scrambler = HighDensityScrambler(0);
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

            auto scrambler = HighDensityScrambler(0);
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