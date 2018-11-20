#include "OutputFileStream.h"

#include <memory>

#include "Format.h"
#include "BasicTraceableException.h"
#include "BasicTraceableExceptionMacros.h"


namespace Handmada::TetraCode::IO {
    OutputFileStream::OutputFileStream(const std::string& fileName)
        : _fout(fileName, std::ios_base::binary)
    {
        if (!_fout) {
            throw Exception::BasicTraceableException(
                Format::str("unable to open file \"{}\"", fileName),
                std::unique_ptr<Exception::TraceableException>()
            );
        }
    }


    void OutputFileStream::write(const byte_t* source, int len)
    {
        _fout.write(reinterpret_cast<const char*>(source), len);
    }
}
