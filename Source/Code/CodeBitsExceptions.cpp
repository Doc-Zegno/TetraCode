#include "CodeBitsExceptions.h"

#include "Format.h"


namespace Handmada::TetraCode::Code {
    // C o r r u p t e d    p a c k e d    b y t e
    CorruptedPackedByteException::CorruptedPackedByteException(
        const std::string& fileName, 
        const std::string& functionName, 
        int line, 
        TraceableExceptionPtr&& cause, 
        byte_t byte
    ) : Exception::BasicTraceableException(
            Format::str("unable to unpack byte 0x{:x}", byte),
            fileName,
            functionName,
            line,
            std::move(cause)
        )
    {
    }


    TraceableExceptionPtr CorruptedPackedByteException::move()
    {
        auto e = new CorruptedPackedByteException(std::move(*this));
        return TraceableExceptionPtr(e);
    }


    TraceableExceptionPtr CorruptedPackedByteException::clone() const
    {
        auto e = new CorruptedPackedByteException(*this);
        return TraceableExceptionPtr(e);
    }



    // B i g    v a l u e    p a c k i n g
    BigValuePackingException::BigValuePackingException(
        const std::string& fileName,
        const std::string& functionName,
        int line,
        TraceableExceptionPtr&& cause,
        int maximum,
        int actual
    ) : Exception::BasicTraceableException(
            Format::str("value {} is too big to be packed (maximum is {})", actual, maximum),
            fileName,
            functionName,
            line,
            std::move(cause)
        )
    {
    }


    TraceableExceptionPtr BigValuePackingException::move()
    {
        auto e = new BigValuePackingException(std::move(*this));
        return TraceableExceptionPtr(e);
    }


    TraceableExceptionPtr BigValuePackingException::clone() const
    {
        auto e = new BigValuePackingException(*this);
        return TraceableExceptionPtr(e);
    }
}
