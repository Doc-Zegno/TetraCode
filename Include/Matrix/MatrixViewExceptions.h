#pragma once

#include "BasicTraceableException.h"
#include "Types.h"


namespace Handmada::TetraCode::Matrix {
	using TraceableExceptionPtr = std::unique_ptr<Exception::TraceableException>;


	/// <summary>
	/// Signalizes that instance of <see cref="MatrixView"/>
	/// tried to call <see cref="get(coord_t, coord_t)"/>
	/// with out of range coordinate
	/// </summary>
	class ViewOutOfRangeException : public Exception::BasicTraceableException {
	public:
		ViewOutOfRangeException(
			const std::string& fileName,
			const std::string& functionName,
			int line,
			TraceableExceptionPtr&& cause
		);

		virtual TraceableExceptionPtr move() override;
		virtual TraceableExceptionPtr clone() const override;
	};


    class ViewSizeMismatchException : public Exception::BasicTraceableException {
    public:
        ViewSizeMismatchException(
            const std::string& fileName,
            const std::string& functionName,
            int line,
            TraceableExceptionPtr&& cause,
            coord_t expected,
            coord_t actual
        );

        virtual TraceableExceptionPtr move() override;
        virtual TraceableExceptionPtr clone() const override;
    };
}
