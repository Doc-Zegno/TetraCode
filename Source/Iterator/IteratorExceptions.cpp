#include "IteratorExceptions.h"


namespace Handmada::TetraCode::Iterator {
    // I n v a l i d    i t e r a t o r
    InvalidIteratorException::InvalidIteratorException(
        const std::string& fileName, 
        const std::string& functionName, 
        int line,
        TraceableExceptionPtr&& cause
    ) : Exception::BasicTraceableException(
            "attempt to use invalid iterator", 
            fileName, 
            functionName, 
            line, 
            std::move(cause)
        )
    {
    }


    TraceableExceptionPtr InvalidIteratorException::move()
    {
        auto e = new InvalidIteratorException(std::move(*this));
        return std::unique_ptr<TraceableException>(e);
    }


    TraceableExceptionPtr InvalidIteratorException::clone() const
    {
        auto e = new InvalidIteratorException(*this);
        return TraceableExceptionPtr(e);
    }



    // C o r r u p t e d    i n p u t
    CorruptedInputSequenceException::CorruptedInputSequenceException(
        const std::string& fileName, 
        const std::string& functionName, 
        int line,
        TraceableExceptionPtr&& cause
    ) : Exception::BasicTraceableException(
            "iterator tried to read corrupted input sequence", 
            fileName, 
            functionName, 
            line, 
            std::move(cause)
        )
    {
    }


    TraceableExceptionPtr CorruptedInputSequenceException::move()
    {
        auto e = new CorruptedInputSequenceException(std::move(*this));
        return std::unique_ptr<TraceableException>(e);
    }


    TraceableExceptionPtr CorruptedInputSequenceException::clone() const
    {
        auto e = new CorruptedInputSequenceException(*this);
        return TraceableExceptionPtr(e);
    }
}
