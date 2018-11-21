#pragma once

#include "Types.h"


namespace Handmada::TetraCode::IO {
    /// <summary>
    /// Abstraction for input byte streams
    /// </summary>
    class InputStream {
    public:
        /// <summary>
        /// Read specified number of bytes from input stream
        /// </summary>
        /// <param name="destination">Destination buffer</param>
        /// <param name="maximumLen">Maximum number of bytes to be read from input stream</param>
        /// <returns>Number of read bytes</returns>
        virtual int read(byte_t* destination, int maximumLen) = 0;

        virtual ~InputStream() { }
    };
}
