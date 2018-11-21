#pragma once

// NOTE: make sure you include this file into .cpp ones only!

// Automatically insert debug info into exception's constructor
#define TooLongSequenceException(cause, optimalSide, maxSide) \
    TooLongSequenceException(__FILE__, __func__, __LINE__, cause, optimalSide, maxSide)
