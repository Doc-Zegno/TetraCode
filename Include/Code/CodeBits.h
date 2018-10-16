#pragma once

#include "Types.h"


namespace Handmada::TetraCode::Code {
    /// <summary>
    /// Encapsulates flags that control the process of <see cref="TetraTree"/>'s expansion
    /// </summary>
    class CodeBits {
    private:
        union {
            struct {
                unsigned isActive1 : 1;
                unsigned isActive2 : 1;
                unsigned isActive3 : 1;
                unsigned isActive4 : 1;
                unsigned colorNumber : 1;
                unsigned brightnessLevel : 3;
            } bits;
            byte_t raw;
        } _converter;

    public:
        CodeBits(byte_t raw);
        CodeBits(const bool(&isActives)[4], int colorNumber, int brightnessLevel);
        
        byte_t toByte() const;
        void getActives(bool (&isActives)[4]) const;
        int numActives() const;
        int brightnessLevel() const;
        int colorNumber() const;
    };
}
