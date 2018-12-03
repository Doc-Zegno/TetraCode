#pragma once


namespace Handmada::TetraCode::Visual {
    /// <summary>
    /// Abstraction for charasteristics of color
    /// </summary>
    class Color {
    private:
        bool _isActive;
        int _huePair;
        int _brightnessLevel;
        int _number;

    public:
        Color();

        /// <param name="isActive">Is <see cref="TetraTree"/>'s node with this color active?</param>
        /// <param name="huePair">Number of color pair</param>
        /// <param name="brightnessLevel">Variation of base color</param>
        /// <param name="number">Number of color within color pair</param>
        Color(bool isActive, int huePair, int brightnessLevel, int number);

        /// <summary>
        /// Check whether this color corresponds to the active <see cref="TetraTree"/>'s node 
        /// </summary>
        /// <returns>`true` if corresponding node is active and `false` otherwise</returns>
        bool isActive() const;

        /// <summary>
        /// Get number of color pair for this color
        /// </summary>
        /// <returns>Color pair's number</returns>
        int huePair() const;

        /// <summary>
        /// Get variation of this color
        /// </summary>
        /// <returns>Color's variation</returns>
        int brightnessLevel() const;

        /// <summary>
        /// Get color number within color pair
        /// </summary>
        /// <returns>Color number</returns>
        int number() const;

        bool operator==(const Color& color) const;
        bool operator!=(const Color& color) const;
    };
}
