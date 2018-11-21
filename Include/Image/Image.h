#pragma once

#include <memory>
#include <string>

#include "Pixel.h"
#include "MatrixView.h"


namespace Handmada::TetraCode::Image {
    /// <summary>
    /// Save image to file
    /// </summary>
    /// <param name="image">Image to be saved</param>
    /// <param name="fileName">Name of the output file</param>
    void exportImage(const Matrix::MatrixView<Visual::Pixel>& image, const std::string& fileName);

    /// <summary>
    /// Import image from file
    /// </summary>
    /// <param name="fileName">Name of the input file</param>
    /// <returns>View of the loaded image</returns>
    std::unique_ptr<Matrix::MatrixView<Visual::Pixel>> importImage(const std::string& fileName);
}