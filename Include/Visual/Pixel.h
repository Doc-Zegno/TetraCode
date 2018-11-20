#pragma once

#include <string>

#include "Types.h"


namespace Handmada::TetraCode::Visual {
    /// <summary>
    /// Immutable representation of a pixel from an image 
    /// </summary>
    class Pixel {
    private:
        byte_t _channels[3];

    public:
        Pixel() = default;
        Pixel(const char* hexCode);
        Pixel(const std::string& hexCode);
        Pixel(byte_t r, byte_t g, byte_t b);

        /// <summary>
        /// Intensity of red channel within [0; 255]
        /// </summary>
        /// <returns>Red channel's value</returns>
        byte_t r() const;

        /// <summary>
        /// Intensity of green channel within [0; 255]
        /// </summary>
        /// <returns>Green channel's value</returns>
        byte_t g() const;

        /// <summary>
        /// Intensity of blue channel within [0; 255]
        /// </summary>
        /// <returns>Blue channel's value</returns>
        byte_t b() const;

        /// <summary>
        /// Get intensity of specified channel
        /// </summary>
        /// <param name="channel">Number of channel within [0; 3)</param>
        /// <returns>Channel's value</returns>
        byte_t operator[](int channel) const;

        /// <summary>
        /// Convert this pixel to its hex code representation
        /// with format of "#rrggbb"
        /// </summary>
        /// <returns>Hex code representation</returns>
        std::string toString() const;

        bool operator==(const Pixel& p) const;
        bool operator!=(const Pixel& p) const;
    };
}
