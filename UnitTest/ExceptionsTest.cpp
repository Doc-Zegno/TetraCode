#include "stdafx.h"
#include "CppUnitTest.h"

#include <vector>
#include <iostream>

#include "Format.h"
#include "IteratorExceptions.h"
#include "IteratorExceptionsMacros.h"
#include "MatrixViewExceptions.h"
#include "MatrixViewExceptionsMacros.h"
#include "BasicTraceableException.h"
#include "BasicTraceableExceptionMacros.h"
#include "CodeBitsExceptions.h"
#include "CodeBitsExceptionsMacros.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Handmada::TetraCode;
using namespace Handmada::TetraCode::Sequence;
using namespace Handmada::TetraCode::Matrix;
using namespace Handmada::TetraCode::Code;
using namespace Handmada::TetraCode::Exception;


namespace UnitTest
{
    TEST_CLASS(ExceptionsTest)
    {
    public:

        TEST_METHOD(ExceptionsCloneMoveTest)
        {
            auto createCause = []() { 
                return TraceableExceptionPtr(
                    new BasicTraceableException("sample text", TraceableExceptionPtr())
                ); 
            };

            TraceableExceptionPtr exceptions[] = {
                TraceableExceptionPtr(new InvalidIteratorException(createCause())),
                TraceableExceptionPtr(new CorruptedInputSequenceException(createCause())),
                TraceableExceptionPtr(new TooLargePaddingException(createCause(), 15, 16)),
                TraceableExceptionPtr(new CorruptedPaddingException(createCause(), 4, 5)),
                TraceableExceptionPtr(new WrongChecksumException(createCause())),
                TraceableExceptionPtr(new TooLargeGroupSizeException(createCause(), 255, 256)),

                TraceableExceptionPtr(new ViewOutOfRangeException(createCause())),
                TraceableExceptionPtr(new ViewSizeMismatchException(createCause(), 6, 7)),
                TraceableExceptionPtr(new ViewBadRatioException(createCause(), 6, 4, 3)),

                TraceableExceptionPtr(new BasicTraceableException("sample text", createCause())),

                TraceableExceptionPtr(new CorruptedPackedByteException(createCause(), 0x00)),
                TraceableExceptionPtr(new BigValuePackingException(createCause(), 15, 16)),
            };


            auto fileName = __FILE__;
            auto functionName = __func__;

            for (auto& e : exceptions) {
                // Test clone
                auto clone = e->clone();
                Assert::AreEqual(fileName, e->fileName().c_str());
                Assert::AreEqual(e->fileName(), clone->fileName());

                Assert::AreEqual(functionName, e->functionName().c_str());
                Assert::AreEqual(e->functionName(), clone->functionName());

                Assert::AreEqual(e->line(), clone->line());

                Assert::IsNotNull(clone->cause());
                Assert::IsNotNull(e->cause());

                // Test move
                auto line = e->line();
                auto moved = e->move();
                Assert::AreEqual(fileName, moved->fileName().c_str());

                Assert::AreEqual(functionName, moved->functionName().c_str());

                Assert::AreEqual(line, moved->line());

                Assert::IsNotNull(moved->cause());
                Assert::IsNull(e->cause());

                // Check that it doesn't throw
                auto str = moved->buildTraceString();
            }
        }

    };
}