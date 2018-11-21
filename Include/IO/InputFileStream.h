#pragma once

#include <string>
#include <fstream>

#include "InputStream.h"


namespace Handmada::TetraCode::IO {
    /// <summary>
    /// Implementation of <see cref="InputStream"/> for binary files
    /// </summary>
    class InputFileStream : public InputStream {
    private:
        std::ifstream _fin;

    public:
        InputFileStream(const std::string& fileName);

        virtual int read(byte_t* destination, int maximumLen) override;
    };
}
