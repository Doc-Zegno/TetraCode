#include "OutputStringStream.h"

#include <cstring>
#include <algorithm>


namespace Handmada::TetraCode::IO {
    OutputStringStream::OutputStringStream(byte_t* start, byte_t* end)
        : _start(start), _end(end)
    {
        _current = _start;
    }


    void OutputStringStream::write(const byte_t* source, int len)
    {
        auto numLeft = int(_end - _current);
        auto numWritten = std::min(numLeft, len);
        std::memcpy(_current, source, numWritten);
        _current += numWritten;
    }
}
