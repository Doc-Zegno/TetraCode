#pragma once

// NOTE: make sure you include this file into .cpp ones only!

// Automatically insert debug info into exception's constructor
#define InvalidIteratorException(cause) \
    InvalidIteratorException(__FILE__, __func__, __LINE__, cause)

// Automatically insert debug info into exception's constructor
#define CorruptedInputSequenceException(cause) \
    CorruptedInputSequenceException(__FILE__, __func__, __LINE__, cause)

// Automatically insert debug info into exception's constructor
#define TooLargePaddingException(cause, maximum, actual) \
    TooLargePaddingException(__FILE__, __func__, __LINE__, cause, maximum, actual)

// Automatically insert debug info into exception's constructor
#define CorruptedPaddingException(cause, expected, actual) \
    CorruptedPaddingException(__FILE__, __func__, __LINE__, cause, expected, actual)

// Automatically insert debug info into exception's constructor
#define WrongChecksumException(cause) \
    WrongChecksumException(__FILE__, __func__, __LINE__, cause)

// Automatically insert debug info into exception's constructor
#define TooLargeGroupSizeException(cause, maximum, actual) \
    TooLargeGroupSizeException(__FILE__, __func__, __LINE__, cause, maximum, actual)
