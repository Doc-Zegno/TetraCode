#pragma once

// NOTE: make sure you include this file into .cpp ones only!

// Automatically insert debug info into exception's constructor
#define InvalidIteratorException(cause) InvalidIteratorException(__FILE__, __func__, __LINE__, cause)

// Automatically insert debug info into exception's constructor
#define CorruptedInputSequenceException(cause) CorruptedInputSequenceException(__FILE__, __func__, __LINE__, cause)
