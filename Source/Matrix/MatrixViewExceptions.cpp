#include "MatrixViewExceptions.h"


namespace Handmada::TetraCode::Matrix {
    // O u t    o f    r a n g e
	ViewOutOfRangeException::ViewOutOfRangeException(
		const std::string& fileName,
		const std::string& functionName,
		int line,
		TraceableExceptionPtr&& cause
	) : Exception::BasicTraceableException(
		    "tried to access non-existing element",
		    fileName,
		    functionName,
		    line,
		    std::move(cause)
	    )
	{
	}


	TraceableExceptionPtr ViewOutOfRangeException::move()
	{
		auto e = new ViewOutOfRangeException(std::move(*this));
		return TraceableExceptionPtr(e);
	}


	TraceableExceptionPtr ViewOutOfRangeException::clone() const
	{
		auto e = new ViewOutOfRangeException(*this);
		return TraceableExceptionPtr(e);
	}



    // S i z e    m i s m a t c h
    ViewSizeMismatchException::ViewSizeMismatchException(
        const std::string& fileName, 
        const std::string& functionName,
        int line,
        TraceableExceptionPtr&& cause,
        coord_t expected,
        coord_t actual
    ) : Exception::BasicTraceableException(
            std::string("size mismatch: expected ")
                + std::to_string(expected)
                + " elements, got "
                + std::to_string(actual),
            fileName,
            functionName,
            line,
            std::move(cause)
        )
    {
    }


    TraceableExceptionPtr ViewSizeMismatchException::move()
    {
        auto e = new ViewSizeMismatchException(std::move(*this));
        return TraceableExceptionPtr(e);
    }


    TraceableExceptionPtr ViewSizeMismatchException::clone() const
    {
        auto e = new ViewSizeMismatchException(*this);
        return TraceableExceptionPtr(e);
    }



    // B a d    r a t i o
    ViewBadRatioException::ViewBadRatioException(
        const std::string& fileName, 
        const std::string& functionName, 
        int line, 
        TraceableExceptionPtr&& cause, 
        coord_t width, 
        coord_t height, 
        int ratio
    ) : Exception::BasicTraceableException(
            std::string("matrix of shape ") 
                + std::to_string(width) + "x" 
                + std::to_string(height)
                + " can't be scaled with ratio " + std::to_string(ratio),
            fileName,
            functionName,
            line,
            std::move(cause)
        )
    {
    }


    TraceableExceptionPtr ViewBadRatioException::move()
    {
        auto e = new ViewBadRatioException(std::move(*this));
        return TraceableExceptionPtr(e);
    }


    TraceableExceptionPtr ViewBadRatioException::clone() const
    {
        auto e = new ViewBadRatioException(*this);
        return TraceableExceptionPtr(e);
    }
}
