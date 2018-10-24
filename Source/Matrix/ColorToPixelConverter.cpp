#include "ColorToPixelConverter.h"


namespace Handmada::TetraCode::Matrix {
	ColorToPixelConverter::ColorToPixelConverter(std::unique_ptr<Visual::Palette>&& palette)
		: _palette(std::move(palette))
	{
	}


	PixelViewPtr ColorToPixelConverter::directView(ColorViewPtr && original) const
	{
		throw std::runtime_error("not implemented");
	}


	ColorViewPtr ColorToPixelConverter::inverseView(PixelViewPtr && converted) const
	{
		throw std::runtime_error("not implemented");
	}
}
