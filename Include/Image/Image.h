#pragma once

#include <memory>

#include "atlimage.h"

#include "Pixel.h"


namespace Handmada::TetraCode::Image {
    void ExportBufferAsImage(const Visual::Pixel* buffer, int width, int height, const char* fileName);
    std::pair<std::unique_ptr<Visual::Pixel[]>, int> ImportImageFromFile(const char* path, bool isVerbose);
}