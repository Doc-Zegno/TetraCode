#include "ColorToPixelConverter.h"

#include "UtilFunctions.h"
#include "MatrixViewExceptions.h"
#include "MatrixViewExceptionsMacros.h"


namespace Handmada::TetraCode::Matrix {
	ColorToPixelConverter::ColorToPixelConverter(std::unique_ptr<Visual::Palette>&& palette) 
        : _palette(std::move(palette))
	{
	}


	PixelViewPtr ColorToPixelConverter::directView(ColorViewPtr&& original) const
	{
        return PixelViewPtr(new DirectView(std::move(original), *_palette));
	}


	ColorViewPtr ColorToPixelConverter::inverseView(PixelViewPtr&& converted) const
	{
        return ColorViewPtr(new InverseView(std::move(converted), *_palette));
	}



	// D i r e c t    v i e w
	ColorToPixelConverter::DirectView::DirectView(
		ColorViewPtr&& view,
		const Visual::Palette& palette
	) : _view(std::move(view)), _palette(palette)
	{
        _width = _view->width();
        _height = _view->height();
	}


	coord_t ColorToPixelConverter::DirectView::width() const
	{
		return _width;
	}


	coord_t ColorToPixelConverter::DirectView::height() const
	{
		return _height;
	}


	Visual::Pixel ColorToPixelConverter::DirectView::get(coord_t x, coord_t y) const
	{
		if (!isInRange(x, _width) || !isInRange(y, _height)) {
			throw ViewOutOfRangeException(TraceableExceptionPtr());
		}
		auto color = _view->get(x, y);
		return _palette.color2pixel(color);
	}



    // I n v e r s e    v i e w
    ColorToPixelConverter::InverseView::InverseView(
        PixelViewPtr&& view, 
        const Visual::Palette& palette
    ) : _view(std::move(view)), _palette(palette)
    {
        _width = _view->width();
        _height = _view->height();
    }


    coord_t ColorToPixelConverter::InverseView::width() const
    {
        return _width;
    }


    coord_t ColorToPixelConverter::InverseView::height() const
    {
        return _height;
    }


    Visual::Color ColorToPixelConverter::InverseView::get(coord_t x, coord_t y) const
    {
        if (!isInRange(x, _width) || !isInRange(y, _height)) {
            throw ViewOutOfRangeException(TraceableExceptionPtr());
        }
        auto pixel = _view->get(x, y);
        return _palette.pixel2color(pixel);
    }
}
