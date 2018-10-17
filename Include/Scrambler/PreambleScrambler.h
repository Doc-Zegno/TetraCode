#pragma once

#include <vector>

#include "Version.h"
#include "Scrambler.h"


namespace Handmada::TetraCode::Scrambler {
    /// <summary>
    /// Concatenates byte representation of TetraCode preamble
    /// (encoding system version)
    /// with input byte sequence
    /// </summary>
    class PreambleScrambler : public Scrambler {
    private:
        union PreamblePacked {
            struct {
                unsigned length : 8;
                unsigned major : 8;
                unsigned minor : 4;
                unsigned micro : 4;
            } fields;
            byte_t raw[3];
        };

        std::vector<byte_t> _preamble;

    public:
        PreambleScrambler(const Version& version);

        virtual ByteIteratorPtr encodingIterator(ByteIteratorPtr&& iterator) const override;
        virtual ByteIteratorPtr decodingIterator(ByteIteratorPtr&& iterator) const override;
    };
}
