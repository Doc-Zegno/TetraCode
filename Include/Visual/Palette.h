#pragma once

#include <cstdint>
#include <map>

#include "Pixel.h"
#include "Color.h"


namespace TetraCode {
	class Palette {
	public:
		virtual Pixel color2pixel(Color color) const = 0;
		virtual Color pixel2color(Pixel pixel) const = 0;
		virtual ~Palette() {}
	};
}