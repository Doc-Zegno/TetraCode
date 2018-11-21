#pragma once

#include <vector>

#include "CodeBitsExceptions.h"
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
        /// <param name="raw">Raw byte to extract code bits from</param>
        CodeBits(byte_t raw);

        /// <param name="isActives">Which children of <see cref="TetraTree"/>'s node should be active?</param>
        /// <param name="colorNumber">Number of color within color pair to encode</param>
        /// <param name="brightnessLevel">Color's variation to encode</param>
        CodeBits(const bool(&isActives)[4], int colorNumber, int brightnessLevel);
        
        /// <summary>
        /// Convert coding bits to raw byte
        /// </summary>
        /// <returns>Raw coding byte</returns>
        byte_t toByte() const;

        /// <summary>
        /// Fill a provided array with boolean flags set for active children of <see cref="TetraTree"/>'s node
        /// </summary>
        void getActives(bool (&isActives)[4]) const;

        /// <summary>
        /// Get number of active children of <see cref="TetraTree"/>'s node
        /// </summary>
        /// <returns>Number of active children</returns>
        int numActives() const;

        /// <summary>
        /// Get variation of encoded color
        /// </summary>
        /// <returns>Encoded color's variation</returns>
        int brightnessLevel() const;

        /// <summary>
        /// Get number of encoded color within color pair
        /// </summary>
        /// <returns>Encoded color's number</returns>
        int colorNumber() const;

        /// <summary>
        /// Get a byte that should be used as an escape one
        /// </summary>
        /// <returns></returns>
        static constexpr byte_t escapeBits() { return byte_t(0b10101111); }

        /// <summary>
        /// Maximum value that can be packed by <see cref="packSmallInt(int)"/> method
        /// </summary>
        /// <returns>Maximum permissible value for packing</returns>
        static constexpr int maxSmallInt() { return 15; }

        /// <summary>
        /// Transform small integer (currently < 16)
        /// into a byte that corresponds to <see cref="TetraTree"/> instance
        /// with 4 active children
        /// </summary>
        /// <param name="value">Integer to be packed</param>
        /// <returns>Packed value</returns>
        static byte_t packSmallInt(int value);

        /// <summary>
        /// Get the original value from packed one
        /// </summary>
        /// <param name="packed">Byte with a packed value</param>
        /// <returns>Original value</returns>
        static int unpackSmallInt(byte_t packed);
    };
}
