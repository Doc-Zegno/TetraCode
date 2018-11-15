#include "EncoderExceptions.h"

#include "Format.h"


namespace Handmada::TetraCode::Code {
    TooLongSequenceException::TooLongSequenceException(
        const std::string& fileName, 
        const std::string& functionName, 
        int line, 
        TraceableExceptionPtr&& cause, 
        coord_t optimalSide, 
        coord_t maxSide
    ) : Exception::BasicTraceableException(
            Format::str("input sequence is too long for image of side {} (optimal is {})", 
                maxSide, optimalSide),
            fileName,
            functionName,
            line,
            std::move(cause)
        )
    {
    }


    TraceableExceptionPtr TooLongSequenceException::move()
    {
        auto e = new TooLongSequenceException(std::move(*this));
        return TraceableExceptionPtr(e);
    }


    TraceableExceptionPtr TooLongSequenceException::clone() const
    {
        auto e = new TooLongSequenceException(*this);
        return TraceableExceptionPtr(e);
    }
}
