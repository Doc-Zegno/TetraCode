#include "Decoder.h" 

#include <queue>

#include "TetraTree.h"


namespace Handmada::TetraCode::Code {
    using Visual::Color;
    using Visual::Palette;
    using Visual::Pixel;


    Decoder::Decoder(const Palette* palette) : _palette(palette)
    {
    }


    std::pair<std::unique_ptr<byte_t[]>, size_t> Decoder::image2sequence(const Pixel* image, coord_t side, coord_t pivotSide) const
    {
        const size_t BUFFER_SIZE = 4096;
        auto buffer = new byte_t[BUFFER_SIZE];

        auto root = TetraTree(0, 0, side, 0, 0, 0);
        buildDecodingTree(&root, image, side, pivotSide);
        auto worklist = std::queue<TetraTree*>();
        worklist.push(&root);

        auto p = buffer;
        while (!worklist.empty()) {
            auto tree = worklist.front();
            worklist.pop();

            auto bits = tree->calculateChildrenCode();
            *p = bits.toByte();
            p++;

            for (auto& child : tree->children()) {
                if (child->color().isActive() && !child->children().empty()) {
                    worklist.push(child.get());
                }
            }
        }

        return std::make_pair(std::unique_ptr<byte_t[]>(buffer), size_t(p - buffer));
    }


    void Decoder::buildDecodingTree(TetraTree* tree, const Pixel* image, coord_t imageSide, coord_t pivotSide) const
    {
        auto stopped = false;
        if (tree->side() == 2 * pivotSide) {
            stopped = true;
        }

        tree->spawnChildren();
        auto hasChildren = false;
        for (auto& child : tree->children()) {
            auto side = child->side();
            auto xMin = child->xMin();
            auto yMin = child->yMin();
            auto xPivot = child->xPivot();
            auto yPivot = child->yPivot();

            auto xMax = xMin + side;
            auto yMax = yMin + side;

            if (xPivot == 0) {
                xMax = xMin + pivotSide;
            } else {
                xMin = xMax - pivotSide;
            }

            if (yPivot == 0) {
                yMax = yMin + pivotSide;
            } else {
                yMin = yMax - pivotSide;
            }

            auto r = 0U;
            auto g = 0U;
            auto b = 0U;
            auto numSamples = 0U;
            for (auto x = xMin; x < xMax; x++) {
                for (auto y = yMin; y < yMax; y++) {
                    auto pixel = image[y * imageSide + x];
                    r += pixel.r();
                    g += pixel.g();
                    b += pixel.b();
                    numSamples++;
                }
            }
            r /= numSamples;
            g /= numSamples;
            b /= numSamples;

            auto color = _palette->pixel2color(Pixel(r, g, b));
            child->setColor(color);
            if (!stopped && child->oddity() == color.huePair()) {
                hasChildren = true;
                buildDecodingTree(child.get(), image, imageSide, pivotSide);
            }
        }

        if (!hasChildren) {
            tree->removeChildren();
        }
    }
}