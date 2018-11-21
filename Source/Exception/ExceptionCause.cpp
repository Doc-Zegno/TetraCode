#include "ExceptionCause.h"


namespace Handmada::TetraCode::Exception {
    ExceptionCause::ExceptionCause(std::unique_ptr<TraceableException>&& exception)
        : _exception(std::move(exception))
    {
    }


    ExceptionCause::ExceptionCause(const ExceptionCause& cause)
    {
        if (cause._exception) {
            _exception = cause._exception->clone();
        }
    }


    const TraceableException* ExceptionCause::get() const
    {
        return _exception.get();
    }
}
