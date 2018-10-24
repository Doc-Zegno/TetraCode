#pragma once

#include "MatrixView.h"


namespace Handmada::TetraCode::Matrix {
	/// <summary>
	/// Basic wrapper around linear (array-like) matrix
	/// </summary>
	template<typename T>
	class BasicView : public MatrixView<T> {
	private:
		const T* _data;
		coord_t _width;
		coord_t _height;

	public:
		BasicView(const T* data, coord_t width, coord_t height);

		virtual coord_t width() const override;
		virtual coord_t height() const override;
		virtual T get(coord_t x, coord_t y) const override;
	};



	template<typename T>
	inline BasicView<T>::BasicView(const T* data, coord_t width, coord_t height)
		: _data(data), _width(width), _height(height)
	{
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
		// TODO: out of range checks and corresponding exception throwing
		return _data[y * _width + x];
	}
}
