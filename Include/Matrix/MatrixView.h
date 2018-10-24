#pragma once

#include "Types.h"


namespace Handmada::TetraCode::Matrix {
	/// <summary>
	/// Generalized interface for **immutable** matrices of type T.
	/// Can be used for creating a lazy matrix to
	/// avoid unnecessary memory allocations
	/// </summary>
	template<typename T>
	class MatrixView {
	public:
		/// <summary>
		/// Get output matrix's width
		/// </summary>
		/// <returns>Matrix's width</returns>
		virtual coord_t width() const = 0;

		/// <summary>
		/// Get output matrix's height
		/// </summary>
		/// <returns>Matrix's height</returns>
		virtual coord_t height() const = 0;

		/// <summary>
		/// Get element of matrix at specified position
		/// </summary>
		/// <param name="x">x-coordinate of position</param>
		/// <param name="y">y-coordinate of position</param>
		/// <returns>Element at position (x, y)</returns>
		virtual T get(coord_t x, coord_t y) const = 0;

		virtual ~MatrixView() { }
	};
}
