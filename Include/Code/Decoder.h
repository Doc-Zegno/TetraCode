#pragma once

#include <memory>

#include "Types.h"
#include "Palette.h"
#include "TetraTree.h"


namespace Handmada::TetraCode::Code {
    class Decoder {
    private:
        const Visual::Palette* _palette;

        void buildDecodingTree(TetraTree* tree,
                               const Visual::Pixel* image,
                               coord_t imageSide,
                               coord_t pivotSide) const;

    public:
        Decoder(const Visual::Palette* palette);

        std::pair<std::unique_ptr<byte_t[]>, size_t> image2sequence(const Visual::Pixel* image, 
                                                                    coord_t side, 
                                                                    coord_t pivotSide) const;
    };
}