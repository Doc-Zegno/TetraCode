#pragma once

#include <memory>

#include "atlimage.h"

#include "Pixel.h"


namespace TetraCode {
	void ExportBufferAsImage(const Pixel* buffer, int width, int height, const char* fileName);
	std::pair<std::unique_ptr<Pixel[]>, int> ImportImageFromFile(const char* path, bool isVerbose);
}