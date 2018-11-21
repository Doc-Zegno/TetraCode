#include "stdafx.h"
#include "CppUnitTest.h"

#include "InputStringStream.h"
#include "OutputStringStream.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Handmada::TetraCode;
using namespace Handmada::TetraCode::IO;


namespace UnitTest
{
    TEST_CLASS(StringStreamTest)
    {
    public:

        TEST_METHOD(InputLoadTest)
        {
            const auto SIZE = 512;  // Don't ask
            byte_t data[SIZE];
            for (auto i = 0; i < SIZE; i++) {
                data[i] = i % 256;
            }

            const auto MAX_LEN = 105;
            int lens[] = { MAX_LEN, MAX_LEN, MAX_LEN, MAX_LEN, 92 };

            byte_t destination[MAX_LEN];
            auto stream = InputStringStream(std::begin(data), std::end(data));
            auto p = std::begin(data);

            auto len = 0;
            auto numBlocks = 0;
            while ((len = stream.read(destination, MAX_LEN)) != 0) {
                Assert::AreEqual(lens[numBlocks], len);
                for (auto i = 0; i < len; i++) {
                    Assert::AreEqual(*p, destination[i]);
                    p++;
                }
                numBlocks++;
            }

            Assert::AreEqual(numBlocks, 5);
        }


        TEST_METHOD(OutputLoadTest)
        {
            const auto SIZE = 512;  // Don't ask
            byte_t data[SIZE];
            for (auto i = 0; i < SIZE; i++) {
                data[i] = i % 256;
            }

            const auto MAX_LEN = 105;
            byte_t destination[SIZE];
            auto stream = OutputStringStream(std::begin(destination), std::end(destination));

            for (auto i = 0; i < 5; i++) {
                stream.write(data + i * MAX_LEN, MAX_LEN);
            }

            for (auto i = 0; i < SIZE; i++) {
                Assert::AreEqual(data[i], destination[i]);
            }
        }

    };
}