#pragma once

#include <memory>

#include "Types.h"
#include "Iterator.h"
#include "OutputStream.h"


namespace Handmada::TetraCode::Sequence {
    /// <summary>
    /// Write byte sequence to the specified output stream
    /// </summary>
    /// <param name="sequence">Byte sequence to be written</param>
    /// <param name="stream">Output byte stream</param>
    void writeSequence(Iterator<byte_t>& sequence, IO::OutputStream& stream);
}
