#pragma once

#include <vector>
#include <memory>
#include <cstdint>

#include "Types.h"
#include "CodeBits.h"
#include "Color.h"


namespace Handmada::TetraCode::Code {
    /// <summary>
    /// Effectively a tree node with at most 4 children.
    /// The main internal data structure of encoder
    /// </summary>
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
        /// <param name="xMin">Minimum x-coordinate of image occupied by this node</param>
        /// <param name="yMin">Minimum y-coordinate of image occupied by this node</param>
        /// <param name="side">Side of image patch occupied by this node</param>
        /// <param name="xPivot">Position of pivot along x-axis (0 or 1)</param>
        /// <param name="yPivot">Position of pivot along y-axis (0 or 1)</param>
        /// <param name="oddity">Oddity of this node within tree hierarchy</param>
        TetraTree(coord_t xMin, coord_t yMin, coord_t side, coord_t xPivot, coord_t yPivot, int oddity);

        /// <summary>
        /// Set color characteristics for this node
        /// </summary>
        /// <param name="color">New color characteristics</param>
        void setColor(const Visual::Color& color);

        /// <summary>
        /// Get list of node's children
        /// </summary>
        /// <returns>Children's list</returns>
        const std::vector<std::unique_ptr<TetraTree>>& children() const;

        /// <summary>
        /// Create 4 dummy children nodes
        /// </summary>
        void spawnChildren();

        /// <summary>
        /// Delete all children nodes
        /// </summary>
        void removeChildren();

        /// <summary>
        /// Set colors for children nodes according to input code byte
        /// </summary>
        /// <param name="bits">Code byte</param>
        void calculateChildrenColors(CodeBits bits);

        /// <summary>
        /// Get code byte according to current colors of children nodes
        /// </summary>
        /// <returns>Code byte</returns>
        CodeBits calculateChildrenCode() const;

        /// <summary>
        /// Calculate the height of the tree starting from this node
        /// </summary>
        /// <returns>Tree's height</returns>
        int calculateHeight() const;

        /// <summary>
        /// Get minimum x-coordinate of image occupied by this node
        /// </summary>
        /// <returns>Minimum x-coordinate of image patch</returns>
        coord_t xMin() const;

        /// <summary>
        /// Get minimum y-coordinate of image occupied by this node
        /// </summary>
        /// <returns>Minimum y-coordinate of image patch</returns>
        coord_t yMin() const;

        /// <summary>
        /// Get side of image patch occupied by this node
        /// </summary>
        /// <returns>Image patch's side</returns>
        coord_t side() const;

        /// <summary>
        /// Get position of node's pivot along x-axis
        /// </summary>
        /// <returns>
        ///     0 if pivot's x-coordinate is `xMin`
        ///     and 1 if it's equal to `xMin` + `side`
        /// </returns>
        coord_t xPivot() const;

        /// <summary>
        /// Get position of node's pivot along y-axis
        /// </summary>
        /// <returns>
        ///     0 if pivot's y-coordinate is `yMin`
        ///     and 1 if it's equal to `yMin` + `side`
        /// </returns>
        coord_t yPivot() const;

        /// <summary>
        /// Get node's oddity
        /// </summary>
        /// <returns>Node's oddity (0 or 1)</returns>
        int oddity() const;

        /// <summary>
        /// Get color characteristics for this node
        /// </summary>
        /// <returns>Node's color characteristics</returns>
        Visual::Color color() const;
    };
}