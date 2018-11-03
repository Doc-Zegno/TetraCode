#include "IteratorExceptions.h"

#include "Format.h"


namespace Handmada::TetraCode::Sequence {
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



    // T o o    l a r g e    p a d d i n g
    TooLargePaddingException::TooLargePaddingException(
        const std::string& fileName, 
        const std::string& functionName, 
        int line, 
        TraceableExceptionPtr&& cause, 
        int maximum, 
        int actual
    ) : Exception::BasicTraceableException(
            std::string("requested padding (")
                + std::to_string(actual)
                + ") is too large (maximum is "
                + std::to_string(maximum)
                + ")",
            fileName,
            functionName,
            line,
            std::move(cause)
        )
    {
    }


    TraceableExceptionPtr TooLargePaddingException::move()
    {
        auto e = new TooLargePaddingException(std::move(*this));
        return TraceableExceptionPtr(e);
    }


    TraceableExceptionPtr TooLargePaddingException::clone() const
    {
        auto e = new TooLargePaddingException(*this);
        return TraceableExceptionPtr(e);
    }



    // C o r r u p t e d    p a d d i n g
    CorruptedPaddingException::CorruptedPaddingException(
        const std::string& fileName, 
        const std::string& functionName, 
        int line, 
        TraceableExceptionPtr&& cause, 
        int expected, 
        int actual
    ) : Exception::BasicTraceableException(
            std::string("corrupted padding byte: expected packed value ")
                + std::to_string(expected)
                + " but got "
                + std::to_string(actual),
            fileName,
            functionName,
            line,
            std::move(cause)
        )
    {
    }


    TraceableExceptionPtr CorruptedPaddingException::move()
    {
        auto e = new CorruptedPaddingException(std::move(*this));
        return TraceableExceptionPtr(e);
    }


    TraceableExceptionPtr CorruptedPaddingException::clone() const
    {
        auto e = new CorruptedPaddingException(*this);
        return TraceableExceptionPtr(e);
    }



    // W r o n g    c h e c k s u m
    WrongChecksumException::WrongChecksumException(
        const std::string& fileName, 
        const std::string& functionName, 
        int line, 
        TraceableExceptionPtr&& cause
    ) : Exception::BasicTraceableException(
            "wrong checksum",
            fileName,
            functionName,
            line,
            std::move(cause)
        )
    {
    }


    TraceableExceptionPtr WrongChecksumException::move()
    {
        auto e = new WrongChecksumException(std::move(*this));
        return TraceableExceptionPtr(e);
    }


    TraceableExceptionPtr WrongChecksumException::clone() const
    {
        auto e = new WrongChecksumException(*this);
        return TraceableExceptionPtr(e);
    }



    // T o o    l a r g e    g r o u p    s i z e
    TooLargeGroupSizeException::TooLargeGroupSizeException(
        const std::string& fileName, 
        const std::string& functionName, 
        int line, 
        TraceableExceptionPtr&& cause, 
        int maximum, 
        int actual
    ) : Exception::BasicTraceableException(
            Format::str("requested group size ({}) is too big (maximum is {})", actual, maximum),
            fileName,
            functionName,
            line,
            std::move(cause)
        )
    {
    }


    TraceableExceptionPtr TooLargeGroupSizeException::move()
    {
        auto e = new TooLargeGroupSizeException(std::move(*this));
        return TraceableExceptionPtr(e);
    }


    TraceableExceptionPtr TooLargeGroupSizeException::clone() const
    {
        auto e = new TooLargeGroupSizeException(*this);
        return TraceableExceptionPtr(e);
    }
}
