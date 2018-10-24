#pragma once

#include "Converter.h"
#include "Color.h"
#include "Pixel.h"
#include "Palette.h"


namespace Handmada::TetraCode::Matrix {
	using PixelViewPtr = MatrixViewPtr<Visual::Pixel>;
	using ColorViewPtr = MatrixViewPtr<Visual::Color>;


	class ColorToPixelConverter : public Converter<Visual::Color, Visual::Pixel> {
	private:
		std::unique_ptr<Visual::Palette> _palette;

	public:
		ColorToPixelConverter(std::unique_ptr<Visual::Palette>&& palette);

		virtual PixelViewPtr directView(ColorViewPtr&& original) const override;
		virtual ColorViewPtr inverseView(PixelViewPtr&& converted) const override;
	};
}
