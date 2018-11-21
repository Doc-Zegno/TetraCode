#include "stdafx.h"
#include "CppUnitTest.h"

#include "ParityCheckScrambler.h"
#include "BasicIterator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Handmada::TetraCode;
using namespace Handmada::TetraCode::Sequence;


namespace UnitTest
{
    TEST_CLASS(ParityScramblerTest)
    {
    public:

        TEST_METHOD(EncodingIteratorTest)
        {
            byte_t bytes[] = { 
                0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                0x21, 0x22, 0x23
            };
            byte_t expected[] = {
                0x07,
                0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF,
                0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0xEF,
                0x21, 0x22, 0x23
            };

            auto scrambler = ParityCheckScrambler(7);
            auto iterator = scrambler.encodingIterator(
                BasicIterator<byte_t>::create(std::begin(bytes), std::end(bytes))
            );
            auto test = [&iterator]() { return iterator->current(); };

            Assert::ExpectException<InvalidIteratorException>(test);
            for (auto e : expected) {
                Assert::IsTrue(iterator->moveNext());
                Assert::AreEqual(e, iterator->current());
            }
            Assert::IsFalse(iterator->moveNext());
            Assert::ExpectException<InvalidIteratorException>(test);
        }


        TEST_METHOD(EncodingIteratorCtorFaultTest)
        {
            byte_t bytes[] = { 0x00, 0x01, 0x02 };

            auto scrambler = ParityCheckScrambler(0xFF + 1);  // Note: more than 1 byte can store
            auto test = [&scrambler, &bytes]() {
                return scrambler.encodingIterator(
                    BasicIterator<byte_t>::create(std::begin(bytes), std::end(bytes))
                );
            };

            Assert::ExpectException<TooLargeGroupSizeException>(test);
        }


        TEST_METHOD(DecodingIteratorTest)
        {
            byte_t expected[] = {
                0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                0x21, 0x22, 0x23
            };

            // Note: groupSize is 7
            byte_t bytes[] = {
                0x07,
                0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF,
                0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0xEF,
                0x21, 0x22, 0x23
            };

            // Note: should work even if expected groupSize (3) is not equal to actual (7)
            auto scrambler = ParityCheckScrambler(3);
            auto iterator = scrambler.decodingIterator(
                BasicIterator<byte_t>::create(std::begin(bytes), std::end(bytes))
            );
            auto test = [&iterator]() { return iterator->current(); };

            Assert::ExpectException<InvalidIteratorException>(test);
            for (auto e : expected) {
                Assert::IsTrue(iterator->moveNext());
                Assert::AreEqual(e, iterator->current());
            }
            Assert::IsFalse(iterator->moveNext());
            Assert::ExpectException<InvalidIteratorException>(test);
        }


        TEST_METHOD(DecodingIteratorCtorFaultTest)
        {
            auto value = byte_t(0);
            auto scrambler = ParityCheckScrambler(7);  // group size doesn't matter

            // Note: empty sequence, group size can't be read
            auto test = [&scrambler, &value]() {
                return scrambler.decodingIterator(
                    BasicIterator<byte_t>::create(&value, &value)
                );
            };

            Assert::ExpectException<CorruptedInputSequenceException>(test);
        }


        TEST_METHOD(DecodingIteratorWrongChecksumTest)
        {
            // Note: groupSize is 7
            // Note: wrong checksum, should be 0xFF
            byte_t bytes[] = {
                0x07,
                0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xEF,
            };

            // Note: should work even if expected groupSize (3) is not equal to actual (7)
            auto scrambler = ParityCheckScrambler(3);
            auto iterator = scrambler.decodingIterator(
                BasicIterator<byte_t>::create(std::begin(bytes), std::end(bytes))
            );

            // Note: should fail when moveNext() is called
            // even if corrupted checksum is still 7 bytes ahead
            auto test = [&iterator]() { return iterator->moveNext(); };

            Assert::ExpectException<WrongChecksumException>(test);
        }

    };
}