#pragma once

#include <memory>

#include "Types.h"
#include "Palette.h"
#include "TetraTree.h"


namespace TetraCode {
    class Decoder {
    private:
        const Palette* _palette;

        void buildDecodingTree(TetraTree* tree, const Pixel* image, coord_t imageSide, coord_t pivotSide) const;

    public:
        Decoder(const Palette* palette);

        std::pair<std::unique_ptr<byte_t[]>, size_t> image2sequence(const Pixel* image, coord_t side, coord_t pivotSide) const;
    };
}