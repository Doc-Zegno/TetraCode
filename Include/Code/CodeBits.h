#pragma once

#include <vector>

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

        /// <summary>
        /// Get a byte that should be used as an escape one
        /// </summary>
        /// <returns></returns>
        static constexpr byte_t escapeBits() { return byte_t(0b10101111); }

        /// <summary>
        /// Transform input byte sequence into one with bytes
        /// that correspond to <see cref="TetraTree"/> instances
        /// with 4 active children
        /// </summary>
        /// <param name="bytes">Original byte sequence</param>
        /// <param name="length">Length of original sequence</param>
        /// <returns>Packed byte sequence</returns>
        static std::vector<byte_t> packBytes(const byte_t* bytes, int length);

        /// <summary>
        /// Transform packed byte sequence into original one
        /// <para>**Note**: exception will be thrown if length is not appropriately rounded</para>
        /// </summary>
        /// <param name="bytes">Packed byte sequence</param>
        /// <param name="length">Length of packed sequence</param>
        /// <returns>Original byte sequence</returns>
        static std::vector<byte_t> unpackBytes(const byte_t* bytes, int length);
    };
}
