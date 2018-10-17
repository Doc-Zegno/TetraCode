#pragma once

#include <memory>

#include "Palette.h"
#include "TetraTree.h"
#include "Pixel.h"


namespace Handmada::TetraCode::Code {
    class Encoder {
    private:
        coord_t _maxSide;
        coord_t _minSide;
        coord_t _pivotSide;
        const Visual::Palette* _palette;

        void fillImage(const TetraTree& tree, Visual::Pixel* image, coord_t optimalSide, coord_t compression) const;

    public:
        Encoder(coord_t maxSide, coord_t minSide, coord_t pivotSide, const Visual::Palette* palette);

        std::pair<std::unique_ptr<Visual::Pixel[]>, int> sequence2image(const byte_t* sequence, size_t length) const;
    };
}