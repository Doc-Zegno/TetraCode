#pragma once

#include <memory>

#include "MatrixView.h"


namespace Handmada::TetraCode::Matrix {
	template<typename T>
	using MatrixViewPtr = std::unique_ptr<MatrixView<T>>;


	/// <summary>
	/// Provides appropriate <see cref="MatrixView"/> implementations
	/// for matrix conversion in both directions
	/// </summary>
	template<typename From, typename To>
	class Converter {
	public:
		/// <summary>
		/// Get an instance of <see cref="MatrixView"/>
		/// which converts matrix beyond specified view
		/// </summary>
		/// <param name="original">View of original matrix</param>
		/// <returns>View for direct conversion</returns>
		virtual MatrixViewPtr<To> directView(MatrixViewPtr<From>&& original) const = 0;

		/// <summary>
		/// Get an instance of <see cref="MatrixView"/>
		/// which converts matrix beyond specified view
		/// back to its original state
		/// </summary>
		/// <param name="converted">View of converted matrix</param>
		/// <returns>View for inverse conversion</returns>
		virtual MatrixViewPtr<From> inverseView(MatrixViewPtr<To>&& converted) const = 0;

		virtual ~Converter() { }
	};
}