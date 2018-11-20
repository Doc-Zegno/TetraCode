#pragma once

#include <memory>

#include "Palette.h"
#include "TetraTree.h"
#include "Iterator.h"
#include "MatrixView.h"
#include "EncoderExceptions.h"


namespace Handmada::TetraCode::Code {
    /// <summary>
    /// Encode input byte sequence into image
    /// </summary>
    /// <param name="sequence">Input byte sequence to be encoded</param>
    /// <param name="maxSide">Maximum side of an output image</param>
    /// <returns>View of image encoding</returns>
    std::unique_ptr<Matrix::MatrixView<Visual::Color>> sequence2image(
        Sequence::Iterator<byte_t>& sequence,
        coord_t maxSide
    );
}