#pragma once

#include <string>

#include "Types.h"


namespace Handmada::TetraCode::Visual {
    /// <summary>
    /// Represents a pixel from an image 
    /// </summary>
    struct Pixel {
        /// <summary>
        /// Intensity of red channel within [0; 255]
        /// </summary>
        byte_t r;

        /// <summary>
        /// Intensity of green channel within [0; 255]
        /// </summary>
        byte_t g;

        /// <summary>
        /// Intensity of blue channel within [0; 255]
        /// </summary>
        byte_t b;

        Pixel() = default;
        Pixel(byte_t r, byte_t g, byte_t b) : r(r), g(g), b(b) { }

        bool operator==(const Pixel& p) const { return r == p.r && g == p.g && b == p.b; }
        bool operator!=(const Pixel& p) const { return r != p.r || g != p.g || b != p.b; }
        std::string toString() const
        {
            char buffer[10] = { 0 };
            snprintf(buffer, 9, "#%02hhx%02hhx%02hhx", r, g, b);
            return std::string(buffer);
        }
    };
}
