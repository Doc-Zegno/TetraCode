#include "stdafx.h"
#include "CppUnitTest.h"

#include "ScramblingPipeline.h"
#include "PreambleScrambler.h"
#include "ParityCheckScrambler.h"
#include "HighDensityScrambler.h"
#include "BasicIterator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Handmada::TetraCode;
using namespace Handmada::TetraCode::Sequence;


namespace UnitTest
{
    TEST_CLASS(ScramblingPipelineTest)
    {
    public:

        TEST_METHOD(EncodingIteratorTest)
        {
            const auto SIZE = 256;
            byte_t bytes[SIZE];
            for (auto i = 0; i < SIZE; i++) {
                bytes[i] = i % 256;
            }

            auto hostVersion = Version(1, 2, 3);
            const auto PADDING = 5;
            const auto GROUP_SIZE = 7;

            // Manual
            auto hd = HighDensityScrambler(PADDING);
            auto checksum = ParityCheckScrambler(GROUP_SIZE);
            auto preamble = PreambleScrambler(hostVersion);
            auto manualIterator = hd.encodingIterator(
                checksum.encodingIterator(
                    preamble.encodingIterator(
                        BasicIterator<byte_t>::create(std::begin(bytes), std::end(bytes))
                    )
                )
            );

            // Automatic
            auto scramblers = std::vector<std::unique_ptr<Scrambler>>();
            scramblers.push_back(PreambleScrambler::create(hostVersion));
            scramblers.push_back(ParityCheckScrambler::create(GROUP_SIZE));
            scramblers.push_back(HighDensityScrambler::create(PADDING));
            auto pipeline = ScramblingPipeline(scramblers);
            auto automaticIterator = pipeline.encodingIterator(
                BasicIterator<byte_t>::create(std::begin(bytes), std::end(bytes))
            );

            // Test
            while (manualIterator->moveNext()) {
                Assert::IsTrue(automaticIterator->moveNext());
                Assert::AreEqual(manualIterator->current(), automaticIterator->current());
            }
            Assert::IsFalse(automaticIterator->moveNext());
        }


        TEST_METHOD(DecodingIteratorTest)
        {
            byte_t bytes[] = {
                0x2F, 0x1F, 0x0F, 0x07, 0x05, 0xAF, 0xFE, 0xAF, 0xCD, 
                0xAF, 0xFF, 0xAF, 0xFF, 0xAF, 0xFE, 0xAF, 0xFD, 0xCA, 0x03
            };

            auto hostVersion = Version(1, 2, 3);  // Doesn't matter
            const auto PADDING = 5;  // Doesn't matter
            const auto GROUP_SIZE = 7;  // Doesn't matter

            // Manual
            auto hd = HighDensityScrambler(PADDING);
            auto checksum = ParityCheckScrambler(GROUP_SIZE);
            auto preamble = PreambleScrambler(hostVersion);
            auto manualIterator = preamble.decodingIterator(
                checksum.decodingIterator(
                    hd.decodingIterator(
                        BasicIterator<byte_t>::create(std::begin(bytes), std::end(bytes))
                    )
                )
            );

            // Automatic
            auto scramblers = std::vector<std::unique_ptr<Scrambler>>();
            scramblers.push_back(PreambleScrambler::create(hostVersion));
            scramblers.push_back(ParityCheckScrambler::create(GROUP_SIZE));
            scramblers.push_back(HighDensityScrambler::create(PADDING));
            auto pipeline = ScramblingPipeline(scramblers);
            auto automaticIterator = pipeline.decodingIterator(
                BasicIterator<byte_t>::create(std::begin(bytes), std::end(bytes))
            );

            // Test
            while (manualIterator->moveNext()) {
                Assert::IsTrue(automaticIterator->moveNext());
                Assert::AreEqual(manualIterator->current(), automaticIterator->current());
            }
            Assert::IsFalse(automaticIterator->moveNext());
        }

    };
}