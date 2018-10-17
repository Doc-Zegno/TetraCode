#include "PreambleScrambler.h"
#include "CodeBits.h"


namespace Handmada::TetraCode::Scrambler {
    PreambleScrambler::PreambleScrambler(const Version& version)
    {
        PreamblePacked packed;
        auto length = sizeof(packed.raw);
        packed.fields.length = length;
        packed.fields.major = version.major;
        packed.fields.minor = version.minor;
        packed.fields.micro = version.micro;
        _preamble = Code::CodeBits::packBytes(packed.raw, length);
    }


    ByteIteratorPtr PreambleScrambler::encodingIterator(ByteIteratorPtr&& iterator) const
    {
        return ByteIteratorPtr();
    }


    ByteIteratorPtr PreambleScrambler::decodingIterator(ByteIteratorPtr&& iterator) const
    {
        return ByteIteratorPtr();
    }
}