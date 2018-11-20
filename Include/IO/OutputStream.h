#pragma once

#include "Types.h"


namespace Handmada::TetraCode::IO {
    /// <summary>
    /// Abstraction for output byte streams
    /// </summary>
    class OutputStream {
    public:
        /// <summary>
        /// Write specified number of bytes from source to this stream
        /// </summary>
        /// <param name="source">Source of output bytes</param>
        /// <param name="len">Number of bytes to be written</param>
        virtual void write(const byte_t* source, int len) = 0;

        virtual ~OutputStream() { }
    };
}
