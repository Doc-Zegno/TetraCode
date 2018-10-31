#include "stdafx.h"
#include "CppUnitTest.h"

#include "Pixel.h"
#include "BasicTraceableException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Handmada::TetraCode::Visual;
using namespace Handmada::TetraCode::Exception;
using namespace Handmada::TetraCode;


namespace UnitTest
{
    TEST_CLASS(PixelTest)
    {
    public:

        TEST_METHOD(BasicFunctionalityTest)
        {
            auto r = byte_t(0xFF);
            auto g = byte_t(0x4A);
            auto b = byte_t(0x20);

            auto pixel = Pixel(r, g, b);
            
            Assert::AreEqual(r, pixel.r());
            Assert::AreEqual(r, pixel[0]);

            Assert::AreEqual(g, pixel.g());
            Assert::AreEqual(g, pixel[1]);

            Assert::AreEqual(b, pixel.b());
            Assert::AreEqual(b, pixel[2]);

            auto test1 = [&pixel]() { return pixel[-1]; };
            auto test2 = [&pixel]() { return pixel[3]; };
            Assert::ExpectException<BasicTraceableException>(test1);
            Assert::ExpectException<BasicTraceableException>(test2);
        }


        TEST_METHOD(EqualityTest)
        {
            auto full = byte_t(0xFF);
            auto zero = byte_t(0x00);

            auto red = Pixel(full, zero, zero);
            auto yellow = Pixel(full, full, zero);

            Assert::IsTrue(red == red);
            Assert::IsFalse(red != red);

            Assert::IsTrue(red != yellow);
            Assert::IsFalse(red == yellow);
        }


        TEST_METHOD(ToStringTest)
        {
            auto r = byte_t(0xFF);
            auto g = byte_t(0x4A);
            auto b = byte_t(0x20);
            auto hexCode = std::string("#ff4a20");
            auto pixel = Pixel(r, g, b);

            Assert::AreEqual(hexCode, pixel.toString());
        }


        TEST_METHOD(StringCtorTest)
        {
            auto hexCode = std::string("#ff4a20");

            // Too short
            auto test1 = []() { return Pixel("#ff4a2"); };
            Assert::ExpectException<BasicTraceableException>(test1);

            // Too long
            auto test2 = []() { return Pixel("#ff4a200"); };
            Assert::ExpectException<BasicTraceableException>(test2);

            // Wrong leading element
            auto test3 = []() { return Pixel("_ff4a20"); };
            Assert::ExpectException<BasicTraceableException>(test3);

            // Corrupted hex code for R channel
            auto test4 = []() { return Pixel("#fz4a20"); };
            Assert::ExpectException<BasicTraceableException>(test4);

            // Corrupted hex code for G channel
            auto test5 = []() { return Pixel("#ff4z20"); };
            Assert::ExpectException<BasicTraceableException>(test5);

            // Corrupted hex code for B channel
            auto test6 = []() { return Pixel("#ff4a2z"); };
            Assert::ExpectException<BasicTraceableException>(test6);

            // Correct
            auto pixel = Pixel(hexCode);
            Assert::AreEqual(hexCode, pixel.toString());
        }

    };
}