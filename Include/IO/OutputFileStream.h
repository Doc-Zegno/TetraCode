#pragma once

#include <string>
#include <fstream>

#include "OutputStream.h"


namespace Handmada::TetraCode::IO {
    /// <summary>
    /// Implementation of <see cref="OutputStream"/> for binary files
    /// </summary>
    class OutputFileStream : public OutputStream {
    private:
        std::ofstream _fout;

    public:
        OutputFileStream(const std::string& fileName);

        virtual void write(const byte_t* source, int len) override;
    };
}
