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
        class DirectView : public MatrixView<Visual::Pixel> {
        private:
            PixelViewPtr _view;
            int _ratio;
            coord_t _width;
            coord_t _height;

        public:
            DirectView(PixelViewPtr&& view, int ratio);

            virtual coord_t width() const override;
            virtual coord_t height() const override;
            virtual Visual::Pixel get(coord_t x, coord_t y) const override;
        };


        class InverseView : public MatrixView<Visual::Pixel> {
        private:
            PixelViewPtr _view;
            int _ratio;
            coord_t _width;
            coord_t _height;

        public:
            InverseView(PixelViewPtr&& view, int ratio);

            virtual coord_t width() const override;
            virtual coord_t height() const override;
            virtual Visual::Pixel get(coord_t x, coord_t y) const override;
        };


        int _ratio;

    public:
        IntegerScalingConverter(int ratio);

        virtual PixelViewPtr directView(PixelViewPtr&& original) const override;
        virtual PixelViewPtr inverseView(PixelViewPtr&& converted) const override;
    };
}

