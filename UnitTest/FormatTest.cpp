#include "stdafx.h"
#include "CppUnitTest.h"

#include "Format.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Handmada::TetraCode;
using namespace Handmada::TetraCode::Exception;


namespace UnitTest
{
    TEST_CLASS(FormatTest)
    {
    public:

        TEST_METHOD(StrTest)
        {
            // Should work on empty format and no arguments
            auto format = "";
            auto actual = Format::str(format);
            Assert::AreEqual(format, actual.c_str());

            // Should work on non-empty format and no arguments
            format = "sample text";
            actual = Format::str(format);
            Assert::AreEqual(format, actual.c_str());

            // Should NOT work on format w/o {} and non-empty argument list
            format = "sample text";
            auto test1 = [format]() { return Format::str(format, "serious arguments"); };
            Assert::ExpectException<BasicTraceableException>(test1);

            // Should NOT work when placeholder is not closed and argument list is empty.
            // I consider it was a programmer's typo
            format = "sample text: {";
            auto test2 = [format]() { return Format::str(format); };
            Assert::ExpectException<BasicTraceableException>(test2);

            // Should NOT work when placeholder is not closed and argument list is not empty
            format = "sample text: {";
            auto test3 = [format]() { return Format::str(format, "serious arguments"); };
            Assert::ExpectException<BasicTraceableException>(test3);

            // Should NOT work on format w/ {} and empty argument list
            format = "sample text: {}";
            auto test4 = [format]() { return Format::str(format); };
            Assert::ExpectException<BasicTraceableException>(test4);

            // Should work on format with 1 {} and 1 argument
            format = "sample text: {}";
            actual = Format::str(format, "serious arguments");
            Assert::AreEqual("sample text: serious arguments", actual.c_str());

            // Should work on homogeneous arguments
            format = "({}, {}, {})";
            actual = Format::str(format, 1, 2, 3);
            Assert::AreEqual("(1, 2, 3)", actual.c_str());

            // Should work on heterogeneous arguments
            format = "({}, {}, {})";
            actual = Format::str(format, 1, 'c', "sample text");
            Assert::AreEqual("(1, c, sample text)", actual.c_str());
        }


        TEST_METHOD(StrOptionsTest)
        {
            // Should work for {:x} and integral input
            auto format = "{} = 0x{:x}";
            auto actual = Format::str(format, 32, 32);
            Assert::AreEqual("32 = 0x20", actual.c_str());

            // Should NOT work for {:x} and non-integral input
            format = "0x{:x}";
            auto test1 = [format]() { return Format::str(format, "serious arguments"); };
            Assert::ExpectException<BasicTraceableException>(test1);

            // Should NOT work for unknown options
            format = "{:z}";
            auto test2 = [format]() { return Format::str(format, 1); };
            Assert::ExpectException<BasicTraceableException>(test2);
        }

    };
}