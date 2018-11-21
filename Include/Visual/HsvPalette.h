#pragma once

#include "Palette.h"


namespace Handmada::TetraCode::Visual {
    class HsvPalette : public Palette
    {
    private:
        Pixel _pixels[2][2][16];

        Color pixel2colorRobust(Pixel pixel) const;
        Color pixel2colorFast(Pixel pixel) const;

    public:
        HsvPalette(const Pixel (&basePixels)[2][2]);

        virtual Pixel color2pixel(Color color) const override;
        virtual Color pixel2color(Pixel pixel) const override;
    };
}

