#pragma once

#include "Types.h"
#include "BasicTraceableException.h"


namespace Handmada::TetraCode::Code {
    using TraceableExceptionPtr = std::unique_ptr<Exception::TraceableException>;


    /// <summary>
    /// Is thrown when corrupted byte is being tried to unpack
    /// </summary>
    class CorruptedPackedByteException : public Exception::BasicTraceableException {
    public:
        CorruptedPackedByteException(
            const std::string& fileName,
            const std::string& functionName,
            int line,
            TraceableExceptionPtr&& cause,
            byte_t byte
        );

        virtual TraceableExceptionPtr move() override;
        virtual TraceableExceptionPtr clone() const override;
    };



    /// <summary>
    /// Is thrown when too big value is being tried to pack
    /// </summary>
    class BigValuePackingException : public Exception::BasicTraceableException {
    public:
        BigValuePackingException(
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
