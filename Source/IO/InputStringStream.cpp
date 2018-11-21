#include "InputStringStream.h"

#include <cstring>
#include <algorithm>


namespace Handmada::TetraCode::IO {
    InputStringStream::InputStringStream(byte_t* begin, byte_t* end)
        : _begin(begin), _end(end)
    {
        _current = _begin;
    }


    int InputStringStream::read(byte_t* destination, int maximumLen)
    {
        auto numLeft = _end - _current;
        auto numRead = std::min(numLeft, maximumLen);
        std::memcpy(destination, _current, numRead);
        _current += numRead;
        return numRead;
    }
}
