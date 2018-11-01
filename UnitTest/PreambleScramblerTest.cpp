#include "stdafx.h"
#include "CppUnitTest.h"

#include "PreambleScrambler.h"
#include "BasicIterator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Handmada::TetraCode;
using namespace Handmada::TetraCode::Sequence;


namespace UnitTest
{
    TEST_CLASS(PreambleScramblerTest)
    {
    public:

        TEST_METHOD(EncodingIteratorTest)
        {
            auto hostVersion = Version(1, 2, 3);
            byte_t bytes[] = { 0x01, 0x02, 0x03 };
            byte_t expected[] = { 0x03, 0x01, 0x32, 0x01, 0x02, 0x03 };

            auto scrambler = PreambleScrambler(hostVersion);
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


        TEST_METHOD(DecodingIteratorTest)
        {
            auto hostVersion = Version(1, 2, 3);
            byte_t bytes[] = { 0x05, 0x01, 0x32, 0x00, 0x00, 0x01, 0x02, 0x03 };
            byte_t expected[] = { 0x01, 0x02, 0x03 };

            auto scrambler = PreambleScrambler(hostVersion);
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

            auto guestVersion = scrambler.guestVersion();
            Assert::AreEqual(guestVersion.toString(), hostVersion.toString());
        }

    };
}