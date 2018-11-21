#include "stdafx.h"
#include "CppUnitTest.h"

#include "Writer.h"
#include "BasicIterator.h"
#include "OutputStringStream.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Handmada::TetraCode;
using namespace Handmada::TetraCode::IO;
using namespace Handmada::TetraCode::Sequence;


namespace UnitTest
{
    TEST_CLASS(WriterTest)
    {
    public:

        TEST_METHOD(LoadTest)
        {
            const auto SIZE = 1024 + 128;  // Don't ask
            byte_t data[SIZE];
            for (auto i = 0; i < SIZE; i++) {
                data[i] = i % 256;
            }

            byte_t destination[SIZE];
            auto stream = OutputStringStream(std::begin(destination), std::end(destination));
            auto sequence = BasicIterator<byte_t>::create(std::begin(data), std::end(data));
            
            writeSequence(*sequence, stream);
            for (auto i = 0; i < SIZE; i++) {
                Assert::AreEqual(data[i], destination[i]);
            }
        }

    };
}