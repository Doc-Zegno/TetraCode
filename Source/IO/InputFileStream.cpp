#include "InputFileStream.h"

#include <memory>

#include "Format.h"
#include "BasicTraceableException.h"
#include "BasicTraceableExceptionMacros.h"


namespace Handmada::TetraCode::IO {
    InputFileStream::InputFileStream(const std::string& fileName)
        : _fin(fileName, std::ios_base::binary)
    {
        if (!_fin) {
            throw Exception::BasicTraceableException(
                Format::str("unable to open file \"{}\"", fileName)
            );
        }
    }


    int InputFileStream::read(byte_t* destination, int maximumLen)
    {
        _fin.read(reinterpret_cast<char*>(destination), maximumLen);
        return int(_fin.gcount());
    }
}
