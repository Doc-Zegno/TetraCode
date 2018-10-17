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


    std::vector<byte_t> CodeBits::packBytes(const byte_t* bytes, int length)
    {
        auto packed = std::vector<byte_t>();
        for (auto i = 0; i < length; i++) {
            auto next = bytes[i];
            auto low = (next & 0x0F) << 4;
            auto high = next & 0xF0;
            packed.push_back(low | 0x0F);
            packed.push_back(high | 0x0F);
        }
        return std::move(packed);
    }


    std::vector<byte_t> CodeBits::unpackBytes(const byte_t* bytes, int length)
    {
        if ((length & 0x01) != 0) {
            throw std::invalid_argument("CodeBits::unpackBytes(): length should be even");
        }

        auto original = std::vector<byte_t>();
        for (auto i = 0; i < length; i += 2) {
            auto low = (bytes[i] & 0xF0) >> 4;
            auto high = bytes[i + 1] & 0xF0;
            original.push_back(high | low);
        }
        return std::move(original);
    }
}