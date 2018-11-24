#pragma once

#include "Converter.h"
#include "Color.h"
#include "Pixel.h"
#include "Palette.h"


namespace Handmada::TetraCode::Matrix {
    using PixelViewPtr = MatrixViewPtr<Visual::Pixel>;
    using ColorViewPtr = MatrixViewPtr<Visual::Color>;


    /// <summary>
    /// Provides client-side classes with instances of <see cref="MatrixView"/>
    /// for converting from matrices of <see cref="Color"/>
    /// to matrices of <see cref="Pixel"/> and vice versa
    /// </summary>
    class ColorToPixelConverter : public Converter<Visual::Color, Visual::Pixel> {
    private:
        class DirectView : public MatrixView<Visual::Pixel> {
        private:
            ColorViewPtr _view;
            const Visual::Palette& _palette;
            coord_t _width;
            coord_t _height;

        public:
            DirectView(ColorViewPtr&& view, const Visual::Palette& palette);

            virtual coord_t width() const override;
            virtual coord_t height() const override;
            virtual Visual::Pixel get(coord_t x, coord_t y) const override;
        };


        class InverseView : public MatrixView<Visual::Color> {
        private:
            PixelViewPtr _view;
            const Visual::Palette& _palette;
            coord_t _width;
            coord_t _height;

        public:
            InverseView(PixelViewPtr&& view, const Visual::Palette& palette);

            virtual coord_t width() const override;
            virtual coord_t height() const override;
            virtual Visual::Color get(coord_t x, coord_t y) const override;
        };


        const Visual::Palette& _palette;

    public:
        ColorToPixelConverter(const Visual::Palette& palette);

        virtual PixelViewPtr directView(ColorViewPtr&& original) const override;
        virtual ColorViewPtr inverseView(PixelViewPtr&& converted) const override;
    };
}
