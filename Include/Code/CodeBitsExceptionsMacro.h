#pragma once

// NOTE: make sure you include this file into .cpp ones only!

// Automatically insert debug info into exception's constructor
#define CorruptedPackedByteException(cause, byte) \
    CorruptedPackedByteException(__FILE__, __func__, __LINE__, cause, byte)

// Automatically insert debug info into exception's constructor
#define BigValuePackingException(cause, maximum, actual) \
    BigValuePackingException(__FILE__, __func__, __LINE__, cause, maximum, actual)