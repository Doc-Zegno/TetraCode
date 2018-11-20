#include "stdafx.h"
#include "CppUnitTest.h"

#include "Encoder.h"
#include "Decoder.h"
#include "BasicIterator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Handmada::TetraCode;
using namespace Handmada::TetraCode::Code;
using namespace Handmada::TetraCode::Sequence;


namespace UnitTest
{
    TEST_CLASS(EncoderDecoderTest)
    {
    public:

        TEST_METHOD(PipelineTest)
        {
            byte_t data[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };
            auto inputIterator = BasicIterator<byte_t>::create(std::begin(data), std::end(data));
            auto view = sequence2image(*inputIterator, 2048);
            auto outputIterator = image2sequence(*view);

            for (auto expected : data) {
                Assert::IsTrue(outputIterator->moveNext());
                Assert::AreEqual(expected, outputIterator->current());
            }
        }

    };
}