#pragma once

#include <memory>

#include "Types.h"
#include "Color.h"
#include "Iterator.h"
#include "MatrixView.h"


namespace Handmada::TetraCode::Code {
    /// <summary>
    /// Decode image into original byte sequence
    /// </summary>
    /// <param name="view">View of input image</param>
    /// <returns>Iterator of original byte sequence</returns>
    std::unique_ptr<Sequence::Iterator<byte_t>> image2sequence(
        const Matrix::MatrixView<Visual::Color>& view
    );
}
