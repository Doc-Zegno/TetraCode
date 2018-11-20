#include "Writer.h"


namespace Handmada::TetraCode::Sequence {
    void writeSequence(Iterator<byte_t>& sequence, IO::OutputStream& stream)
    {
        const auto BUFFER_SIZE = 256;
        byte_t buffer[BUFFER_SIZE];
        
        auto p = buffer;
        auto end = buffer + BUFFER_SIZE;
        while (sequence.moveNext()) {
            *p = sequence.current();
            p++;

            if (p >= end) {
                // Flush buffer
                stream.write(buffer, BUFFER_SIZE);
                p = buffer;
            }
        }

        // Flush remaining bytes
        stream.write(buffer, p - buffer);
    }
}
