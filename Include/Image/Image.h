#pragma once

#include <memory>
#include <string>

#include "Pixel.h"
#include "MatrixView.h"


namespace Handmada::TetraCode::Image {
    void exportImage(const Matrix::MatrixView<Visual::Pixel>& image, const std::string& fileName);

    // Deprecated
    std::pair<std::unique_ptr<Visual::Pixel[]>, int> ImportImageFromFile(const char* path, bool isVerbose);
}