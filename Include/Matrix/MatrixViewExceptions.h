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



    /// <summary>
    /// Signalizes that instance of <see cref="MatrixView"/>
    /// is being constructed over a container which size
    /// is not equal to a product of expected height and width of matrix
    /// </summary>
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



    /// <summary>
    /// Signalizes that instance of <see cref="MatrixView"/>
    /// (usually a scaling one) is being constructed
    /// with incompatible combination of width, height and scaling ratio
    /// </summary>
    class ViewBadRatioException : public Exception::BasicTraceableException {
    public:
        ViewBadRatioException(
            const std::string& fileName,
            const std::string& functionName,
            int line,
            TraceableExceptionPtr&& cause,
            coord_t width,
            coord_t height,
            int ratio
        );

        virtual TraceableExceptionPtr move() override;
        virtual TraceableExceptionPtr clone() const override;
    };
}
