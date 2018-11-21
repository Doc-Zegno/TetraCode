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


        TEST_METHOD(UnpackSmallIntFaultTest)
        {
            auto packed = byte_t(0x5D);  // Note: all of least 4 bits must be set
            auto test = [packed]() { return CodeBits::unpackSmallInt(packed); };
            Assert::ExpectException<CorruptedPackedByteException>(test);
        }


        TEST_METHOD(PackSmallIntBigInputTest)
        {
            auto value = CodeBits::maxSmallInt() + 1;
            auto test = [value]() { return CodeBits::packSmallInt(value); };
            Assert::ExpectException<BigValuePackingException>(test);
        }

    };
}