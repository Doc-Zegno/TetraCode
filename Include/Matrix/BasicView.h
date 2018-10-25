#pragma once

#include <vector>

#include "MatrixView.h"
#include "MatrixViewExceptions.h"
#include "UtilFunctions.h"


namespace Handmada::TetraCode::Matrix {
	/// <summary>
	/// Basic wrapper around linear (array-like) matrix.
	/// For proper memory management, matrix should be encapsulated in vector
	/// </summary>
	template<typename T>
	class BasicView : public MatrixView<T> {
	private:
		std::vector<T> _data;
		coord_t _width;
		coord_t _height;

	public:
		BasicView(std::vector<T>&& data, coord_t width, coord_t height);

		virtual coord_t width() const override;
		virtual coord_t height() const override;
		virtual T get(coord_t x, coord_t y) const override;
	};



	template<typename T>
	inline BasicView<T>::BasicView(std::vector<T>&& data, coord_t width, coord_t height)
		: _data(std::move(data)), _width(width), _height(height)
	{
        auto expected = width * height;
        auto actual = _data.size();
        if (expected != actual) {
            throw ViewSizeMismatchException(
                __FILE__, 
                __func__, 
                __LINE__, 
                TraceableExceptionPtr(), 
                expected, 
                actual
            );
        }
	}


	template<typename T>
	inline coord_t BasicView<T>::width() const
	{
		return _width;
	}


	template<typename T>
	inline coord_t BasicView<T>::height() const
	{
		return _height;
	}


	template<typename T>
	inline T BasicView<T>::get(coord_t x, coord_t y) const
	{
		if (!isInRange(x, _width) || !isInRange(y, _height)) {
			throw ViewOutOfRangeException(__FILE__, __func__, __LINE__, TraceableExceptionPtr());
		}
		return _data[y * _width + x];
	}
}
