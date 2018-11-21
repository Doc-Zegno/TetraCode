#pragma once

#include <memory>

#include "Types.h"
#include "Iterator.h"
#include "InputStream.h"


namespace Handmada::TetraCode::Sequence {
    /// <summary>
    /// Read a byte sequence from the specified input stream
    /// </summary>
    /// <param name="stream">Input byte stream</param>
    /// <returns>Reading byte iterator</returns>
    std::unique_ptr<Iterator<byte_t>> readSequence(IO::InputStream& stream);
}
