#include "CodeBits.h"


namespace Handmada::TetraCode::Code {
    CodeBits::CodeBits(byte_t raw)
    {
        _converter.raw = raw;
    }


    CodeBits::CodeBits(const bool (&isActives)[4], int colorNumber, int brightnessLevel)
    {
        _converter.bits.isActive1 = isActives[0];
        _converter.bits.isActive2 = isActives[1];
        _converter.bits.isActive3 = isActives[2];
        _converter.bits.isActive4 = isActives[3];

        _converter.bits.colorNumber = colorNumber;
        _converter.bits.brightnessLevel = brightnessLevel;
    }


    byte_t CodeBits::toByte() const
    {
        return _converter.raw;
    }


    void CodeBits::getActives(bool (&isActives)[4]) const
    {
        isActives[0] = _converter.bits.isActive1;
        isActives[1] = _converter.bits.isActive2;
        isActives[2] = _converter.bits.isActive3;
        isActives[3] = _converter.bits.isActive4;
    }


    int CodeBits::numActives() const
    {
        return _converter.bits.isActive1 + _converter.bits.isActive2
            + _converter.bits.isActive3 + _converter.bits.isActive4;
    }


    int CodeBits::brightnessLevel() const
    {
        return _converter.bits.brightnessLevel;
    }


    int CodeBits::colorNumber() const
    {
        return _converter.bits.colorNumber;
    }
}