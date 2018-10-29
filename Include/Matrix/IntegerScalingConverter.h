#pragma once

#include "Converter.h"
#include "Pixel.h"


namespace Handmada::TetraCode::Matrix {
    using PixelViewPtr = MatrixViewPtr<Visual::Pixel>;


    /// <summary>
    /// Scales input <see cref="MatrixView"/> with integer ratio
    /// </summary>
    class IntegerScalingConverter : public Converter<Visual::Pixel, Visual::Pixel> {
    private:
        int _ratio;

    public:
        IntegerScalingConverter(int ratio);

        virtual PixelViewPtr directView(PixelViewPtr&& original) const override;
        virtual PixelViewPtr inverseView(PixelViewPtr&& converted) const override;
    };
}

