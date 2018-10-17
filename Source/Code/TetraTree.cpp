#include "TetraTree.h"

#include <algorithm>


namespace Handmada::TetraCode::Code {
    using Visual::Color;


    TetraTree::TetraTree(coord_t xMin, coord_t yMin, coord_t side, coord_t xPivot, coord_t yPivot, int oddity)
        : _xMin(xMin), _yMin(yMin), _side(side), _xPivot(xPivot), _yPivot(yPivot), _oddity(oddity)
    {
    }


    void TetraTree::setColor(const Color& color)
    {
        _color = color;
    }


    const std::vector<std::unique_ptr<TetraTree>>& TetraTree::children() const
    {
        return _children;
    }


    void TetraTree::spawnChildren()
    {
        auto side = _side >> 1;
        auto oddity = 1 - _oddity;

        coord_t indices[4][2] = {
            { 0, 0 },
            { 0, 1 },
            { 1, 1 },
            { 1, 0 },
        };

        for (auto index = 0; index < 4; index++) {
            auto i = indices[index][0];
            auto j = indices[index][1];

            auto xMin = _xMin + j * side;
            auto yMin = _yMin + i * side;
            auto xPivot = 1U - j;
            auto yPivot = 1U - i;

            auto child = new TetraTree(xMin, yMin, side, xPivot, yPivot, oddity);
            _children.push_back(std::unique_ptr<TetraTree>(child));
        }
    }


    void TetraTree::removeChildren()
    {
        _children.clear();
    }


    void TetraTree::calculateChildrenColors(CodeBits bits)
    {
        bool isActives[4];
        bits.getActives(isActives);

        for (auto i = 0; i < 4; i++) {
            auto colorNumber = bits.colorNumber();
            if (!isActives[i]) {
                colorNumber = 1 - colorNumber;
            }

            _children[i]->setColor(Color(isActives[i], 1 - _oddity, bits.brightnessLevel(), colorNumber));
        }
    }


    CodeBits TetraTree::calculateChildrenCode() const
    {
        bool isActives[4];
        auto colorNumber = 0;
        auto huePair = 0;
        auto brightnessLevel = 0;

        for (auto i = 0; i < 4; i++) {
            auto color = _children[i]->color();
            isActives[i] = color.isActive();

            if (i == 0) {
                colorNumber = color.number();
                if (!isActives[0]) {
                    colorNumber = 1 - colorNumber;
                }

                brightnessLevel = color.brightnessLevel();
                huePair = color.huePair();
            }
        }

        return CodeBits(isActives, colorNumber, brightnessLevel);
    }


    int TetraTree::calculateHeight() const
    {
        if (_children.empty()) {
            return 0;
        } else {
            auto maxHeight = 0;
            for (auto& child : _children) {
                maxHeight = std::max(maxHeight, child->calculateHeight());
            }
            return maxHeight + 1;
        }
    }


    coord_t TetraTree::xMin() const
    {
        return _xMin;
    }


    coord_t TetraTree::yMin() const
    {
        return _yMin;
    }


    coord_t TetraTree::side() const
    {
        return _side;
    }


    coord_t TetraTree::xPivot() const
    {
        return _xPivot;
    }


    coord_t TetraTree::yPivot() const
    {
        return _yPivot;
    }


    int TetraTree::oddity() const
    {
        return _oddity;
    }


    Color TetraTree::color() const
    {
        return _color;
    }
}