#pragma once

#include <vector>
#include <memory>
#include <cstdint>

#include "Types.h"
#include "CodeBits.h"
#include "Color.h"


namespace Handmada::TetraCode::Code {
    class TetraTree {
    private:
        std::vector<std::unique_ptr<TetraTree>> _children;

        coord_t _xMin;
        coord_t _yMin;
        coord_t _side;
        coord_t _xPivot;
        coord_t _yPivot;
        int _oddity;
        Visual::Color _color;

    public:
        TetraTree(coord_t xMin, coord_t yMin, coord_t side, coord_t xPivot, coord_t yPivot, int oddity);

        void setColor(const Visual::Color& color);
        const std::vector<std::unique_ptr<TetraTree>>& children() const;
        void spawnChildren();
        void removeChildren();
        void calculateChildrenColors(CodeBits bits);
        CodeBits calculateChildrenCode() const;
        int calculateHeight() const;

        coord_t xMin() const;
        coord_t yMin() const;
        coord_t side() const;
        coord_t xPivot() const;
        coord_t yPivot() const;
        int oddity() const;
        Visual::Color color() const;
    };
}