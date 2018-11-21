#pragma once

#include "OutputStream.h"


namespace Handmada::TetraCode::IO {
    /// <summary>
    /// Implementation of <see cref="OutputStream"/> for byte strings (arrays)
    /// </summary>
    class OutputStringStream : public OutputStream {
    private:
        byte_t* _start;
        byte_t* _end;
        byte_t* _current;

    public:
        OutputStringStream(byte_t* start, byte_t* end);

        virtual void write(const byte_t * source, int len) override;
    };
}
