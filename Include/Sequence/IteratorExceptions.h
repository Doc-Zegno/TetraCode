#pragma once

#include "Types.h"
#include "BasicTraceableException.h"


namespace Handmada::TetraCode::Sequence {
    using TraceableExceptionPtr = std::unique_ptr<Exception::TraceableException>;


    /// <summary>
    /// Signalizes that instance of <see cref="Iterator"/>
    /// is being used in condition when it must not
    /// </summary>
    class InvalidIteratorException : public Exception::BasicTraceableException {
    public:
        InvalidIteratorException(
            const std::string& fileName,
            const std::string& functionName,
            int line,
            TraceableExceptionPtr&& cause
        );

        virtual TraceableExceptionPtr move() override;
        virtual TraceableExceptionPtr clone() const override;
    };



    /// <summary>
    /// Signalizes that <see cref="Iterator"/> instance
    /// has failed to parse input sequence as it was corrupted
    /// </summary>
    class CorruptedInputSequenceException : public Exception::BasicTraceableException {
    public:
        CorruptedInputSequenceException(
            const std::string& fileName,
            const std::string& functionName,
            int line,
            TraceableExceptionPtr&& cause
        );

        virtual TraceableExceptionPtr move() override;
        virtual TraceableExceptionPtr clone() const override;
    };



    /// <summary>
    /// Signalizes that <see cref="Iterator"/> instance
    /// tried to make a byte padding larger than
    /// underlying coding system allows
    /// </summary>
    class TooLargePaddingException : public Exception::BasicTraceableException {
    public:
        TooLargePaddingException(
            const std::string& fileName,
            const std::string& functionName,
            int line,
            TraceableExceptionPtr&& cause,
            int maximum,
            int actual
        );

        virtual TraceableExceptionPtr move() override;
        virtual TraceableExceptionPtr clone() const override;
    };



    /// <summary>
    /// Signalizes that <see cref="Iterator"/> instance
    /// failed to remove padding bytes from input sequence
    /// since they were corrupted
    /// </summary>
    class CorruptedPaddingException : public Exception::BasicTraceableException {
    public:
        CorruptedPaddingException(
            const std::string& fileName,
            const std::string& functionName,
            int line,
            TraceableExceptionPtr&& cause,
            int expected,
            int actual
        );

        virtual TraceableExceptionPtr move() override;
        virtual TraceableExceptionPtr clone() const override;
    };



    /// <summary>
    /// Signalizes that <see cref="Iterator"/> instance
    /// has calculated checksum different from the one provided by input sequence
    /// </summary>
    class WrongChecksumException : public Exception::BasicTraceableException {
    public:
        WrongChecksumException(
            const std::string& fileName,
            const std::string& functionName,
            int line,
            TraceableExceptionPtr&& cause,
            byte_t expected,
            byte_t actual
        );

        virtual TraceableExceptionPtr move() override;
        virtual TraceableExceptionPtr clone() const override;
    };


    /// <summary>
    /// Signalizes that <see cref="Iterator"/> instance
    /// has been told to use group size for checksums
    /// that is too large
    /// </summary>
    class TooLargeGroupSizeException : public Exception::BasicTraceableException {
    public:
        TooLargeGroupSizeException(
            const std::string& fileName,
            const std::string& functionName,
            int line,
            TraceableExceptionPtr&& cause,
            int maximum,
            int actual
        );

        virtual TraceableExceptionPtr move() override;
        virtual TraceableExceptionPtr clone() const override;
    };
}
