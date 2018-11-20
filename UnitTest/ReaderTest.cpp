#include "stdafx.h"
#include "CppUnitTest.h"

#include "Reader.h"
#include "InputStringStream.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Handmada::TetraCode;
using namespace Handmada::TetraCode::IO;
using namespace Handmada::TetraCode::Sequence;


namespace UnitTest
{
    TEST_CLASS(ReaderTest)
    {
    public:

        TEST_METHOD(LoadTest)
        {
            const auto SIZE = 1024 + 128;  // Don't ask
            byte_t data[SIZE];
            for (auto i = 0; i < SIZE; i++) {
                data[i] = i % 256;
            }

            auto stream = InputStringStream(std::begin(data), std::end(data));
            auto iterator = readSequence(stream);
            auto test = [&iterator]() { return iterator->current(); };
            
            // Should throw on start
            Assert::ExpectException<InvalidIteratorException>(test);

            for (auto expected : data) {
                Assert::IsTrue(iterator->moveNext());
                Assert::AreEqual(expected, iterator->current());
            }

            Assert::IsFalse(iterator->moveNext());
            Assert::ExpectException<InvalidIteratorException>(test);
        }

    };
}