#pragma once

#include "InputStream.h"


namespace Handmada::TetraCode::IO {
    /// <summary>
    /// Implementation of <see cref="InputStream"/> for byte strings (arrays)
    /// </summary>
    class InputStringStream : public InputStream {
    private:
        byte_t* _begin;
        byte_t* _end;
        byte_t* _current;

    public:
        InputStringStream(byte_t* begin, byte_t* end);

        virtual int read(byte_t* destination, int maximumLen) override;
    };
}