#pragma once

// NOTE: make sure you include this file into .cpp ones only!

// Automatically insert debug info into exception's constructor
#define ViewOutOfRangeException(cause) ViewOutOfRangeException(__FILE__, __func__, __LINE__, cause)

// Automatically insert debug info into exception's constructor
#define ViewSizeMismatchException(cause, expected, actual) \
    ViewSizeMismatchException(__FILE__, __func__, __LINE__, cause, expected, actual)
