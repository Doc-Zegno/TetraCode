#include "Encoder.h"

#include <vector>
#include <algorithm>

#include "BasicView.h"
#include "EncoderExceptionsMacros.h"


namespace Handmada::TetraCode::Code {
    using Visual::Color;
    using Sequence::Iterator;
    using Matrix::MatrixView;
    using Matrix::BasicView;


    static void fillFrame(const TetraTree& tree, Color* image, coord_t optimalSide, coord_t compression)
    {
        auto side = tree.side() / compression;
        auto xMin = tree.xMin() / compression;
        auto yMin = tree.yMin() / compression;
        auto xMax = xMin + side;
        auto yMax = yMin + side;
        auto color = tree.color();

        if (!tree.children().empty()) {
            for (auto& child : tree.children()) {
                fillFrame(*child, image, optimalSide, compression);
            }

            if (tree.xPivot() == 1U) {
                xMin = xMax - 1;
            } else {
                xMax = xMin + 1;
            }

            if (tree.yPivot() == 1U) {
                yMin = yMax - 1;
            } else {
                yMax = yMin + 1;
            }
        }

        for (auto x = xMin; x < xMax; x++) {
            for (auto y = yMin; y < yMax; y++) {
                image[y * optimalSide + x] = color;
            }
        }
    }


    std::unique_ptr<MatrixView<Color>> sequence2image(
        Iterator<byte_t>& sequence,
        coord_t maxSide,
        coord_t minSide
    )
    {
        TetraTree root(0U, 0U, maxSide, 0U, 0U, 0);

        std::vector<TetraTree*> stack = { &root };
        for (auto index = 0; sequence.moveNext(); index++) {
            auto tree = stack[index];
            tree->spawnChildren();
            tree->calculateChildrenColors(CodeBits(sequence.current()));

            for (auto& child : tree->children()) {
                if (child->color().isActive()) {
                    stack.push_back(child.get());
                }
            }
        }

        auto calculatedSide = coord_t((1 << root.calculateHeight()) * 2);
        auto optimalSide = std::max(calculatedSide, minSide);
        if (optimalSide > maxSide) {
            throw TooLongSequenceException(TraceableExceptionPtr(), optimalSide, maxSide);
        }

        auto compression = maxSide / optimalSide;

        auto frame = std::vector<Color>(optimalSide * optimalSide, Color());
        fillFrame(root, frame.data(), optimalSide, compression);
        return BasicView<Color>::create(std::move(frame), optimalSide, optimalSide);
    }
}