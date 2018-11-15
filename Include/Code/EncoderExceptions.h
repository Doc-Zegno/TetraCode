#pragma once

#include "Types.h"
#include "BasicTraceableException.h"


namespace Handmada::TetraCode::Code {
    using TraceableExceptionPtr = std::unique_ptr<Exception::TraceableException>;


    /// <summary>
    /// Signalizes that input byte sequence is too long to fit it inside
    /// a matrix of side `maxSide`
    /// </summary>
    class TooLongSequenceException : public Exception::BasicTraceableException {
    public:
        TooLongSequenceException(
            const std::string& fileName,
            const std::string& functionName,
            int line,
            TraceableExceptionPtr&& cause,
            coord_t optimalSide,
            coord_t maxSide
        );

        virtual TraceableExceptionPtr move() override;
        virtual TraceableExceptionPtr clone() const override;
    };

}
