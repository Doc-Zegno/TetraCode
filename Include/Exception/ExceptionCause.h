#pragma once

#include "TraceableException.h"


namespace Handmada::TetraCode::Exception {
    /// <summary>
    /// Stores exception and allows to copy it.
    /// Effectively provides copying functionality for `unique_ptr`
    /// to <see cref="TraceableException"/>
    /// </summary>
    class ExceptionCause {
    private:
        std::unique_ptr<TraceableException> _exception;

    public:
        ExceptionCause(std::unique_ptr<TraceableException>&& exception);
        ExceptionCause(const ExceptionCause& cause);
        ExceptionCause(ExceptionCause&& cause) = default;

        /// <summary>
        /// Return pointer to instance of <see cref="TraceableException"/>
        /// that was a cause of another exception
        /// </summary>
        /// <returns>Pointer to cause</returns>
        const TraceableException* get() const;
    };
}
