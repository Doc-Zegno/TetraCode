#pragma once

#include "Types.h"


namespace Handmada::TetraCode::Visual {
    struct Pixel {
        byte_t r;
        byte_t g;
        byte_t b;

        Pixel() = default;
        Pixel(byte_t r, byte_t g, byte_t b) : r(r), g(g), b(b) { }
    };
}
