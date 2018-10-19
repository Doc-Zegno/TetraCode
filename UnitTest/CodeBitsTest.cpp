#include "stdafx.h"
#include "CppUnitTest.h"

#include "CodeBits.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Handmada::TetraCode;
using namespace Handmada::TetraCode::Code;


namespace UnitTest
{
    TEST_CLASS(CodeBitsTest)
    {
    public:

        TEST_METHOD(PackSmallIntTest)
        {
            auto value = 5;
            auto expected = byte_t(0x5F);
            auto actual = CodeBits::packSmallInt(value);
            Assert::AreEqual(expected, actual);
        }


        TEST_METHOD(UnpackSmallIntTest)
        {
            auto packed = byte_t(0x5F);
            auto expected = 5;
            auto actual = CodeBits::unpackSmallInt(packed);
            Assert::AreEqual(expected, actual);
        }


        TEST_METHOD(PackSmallIntBigInputTest)
        {
            auto value = CodeBits::maxSmallInt() + 1;
            auto test = [value]() { return CodeBits::packSmallInt(value); };
            Assert::ExpectException<std::invalid_argument>(test);
        }


        // TODO: remove
        TEST_METHOD(PackBytesTest)
        {
            byte_t bytes[] = { 1, 2, 3, 4, 5 };
            byte_t expected[] = { 0x1F, 0x0F, 0x2F, 0x0F, 0x3F, 0x0F, 0x4F, 0x0F, 0x5F, 0x0F };
            auto actual = CodeBits::packBytes(bytes, sizeof(bytes));

            Assert::AreEqual(sizeof(expected), actual.size());
            for (auto i = 0U; i < actual.size(); i++) {
                Assert::AreEqual(expected[i], actual[i]);
            }
        }


        // TODO: remove
        TEST_METHOD(UnpackBytesTest)
        {
            byte_t bytes[] = { 0x1F, 0x0F, 0x2F, 0x0F, 0x3F, 0x0F, 0x4F, 0x0F, 0x5F, 0x0F };
            byte_t expected[] = { 1, 2, 3, 4, 5 };
            auto actual = CodeBits::unpackBytes(bytes, sizeof(bytes));

            Assert::AreEqual(sizeof(expected), actual.size());
            for (auto i = 0U; i < actual.size(); i++) {
                Assert::AreEqual(expected[i], actual[i]);
            }
        }


        // TODO: remove
        TEST_METHOD(UnpackBytesBadRoundingTest)
        {
            byte_t bytes[] = { 0x1F, 0x0F, 0x2F, 0x0F, 0x3F, 0x0F, 0x4F, 0x0F, 0x5F };
            auto test = [bytes]() { return CodeBits::unpackBytes(bytes, sizeof(bytes)); };
            Assert::ExpectException<std::invalid_argument>(test);
        }

    };
}