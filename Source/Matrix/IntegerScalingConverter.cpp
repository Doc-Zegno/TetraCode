#include "IntegerScalingConverter.h"

#include "UtilFunctions.h"
#include "MatrixViewExceptions.h"
#include "MatrixViewExceptionsMacros.h"


namespace Handmada::TetraCode::Matrix {
    IntegerScalingConverter::IntegerScalingConverter(int ratio)
        : _ratio(ratio)
    {
    }


    PixelViewPtr IntegerScalingConverter::directView(PixelViewPtr&& original) const
    {
        return PixelViewPtr(new DirectView(std::move(original), _ratio));
    }


    PixelViewPtr IntegerScalingConverter::inverseView(PixelViewPtr&& converted) const
    {
        return PixelViewPtr(new InverseView(std::move(converted), _ratio));
    }



    // D i r e c t    v i e w
    IntegerScalingConverter::DirectView::DirectView(PixelViewPtr&& view, int ratio)
        : _view(std::move(view)), _ratio(ratio)
    {
        _width = _view->width() * ratio;
        _height = _view->height() * ratio;
    }


    coord_t IntegerScalingConverter::DirectView::width() const
    {
        return _width;
    }


    coord_t IntegerScalingConverter::DirectView::height() const
    {
        return _height;
    }


    Visual::Pixel IntegerScalingConverter::DirectView::get(coord_t x, coord_t y) const
    {
        if (!isInRange(x, _width) || !isInRange(y, _height)) {
            throw ViewOutOfRangeException(TraceableExceptionPtr());
        }

        return _view->get(x / _ratio, y / _ratio);
    }



    // I n v e r s e    v i e w
    IntegerScalingConverter::InverseView::InverseView(PixelViewPtr&& view, int ratio)
        : _view(std::move(view)), _ratio(ratio)
    {
        auto width = _view->width();
        auto height = _view->height();

        if (width % ratio != 0 || height % ratio != 0) {
            throw ViewBadRatioException(TraceableExceptionPtr(), width, height, ratio);
        }

        _width = width / ratio;
        _height = height / ratio;
    }


    coord_t IntegerScalingConverter::InverseView::width() const
    {
        return _width;
    }


    coord_t IntegerScalingConverter::InverseView::height() const
    {
        return _height;
    }


    Visual::Pixel IntegerScalingConverter::InverseView::get(coord_t x, coord_t y) const
    {
        if (!isInRange(x, _width) || !isInRange(y, _height)) {
            throw ViewOutOfRangeException(TraceableExceptionPtr());
        }

        auto xMin = x * _ratio;
        auto yMin = y * _ratio;
        auto xMax = xMin + _ratio;
        auto yMax = yMin + _ratio;

        auto r = 0;
        auto g = 0;
        auto b = 0;

        for (auto x = xMin; x < xMax; x++) {
            for (auto y = yMin; y < yMax; y++) {
                auto pixel = _view->get(x, y);
                r += pixel.r();
                g += pixel.g();
                b += pixel.b();
            }
        }

        auto num = _ratio * _ratio;
        r /= num;
        g /= num;
        b /= num;

        return Visual::Pixel(r, g, b);
    }
}
