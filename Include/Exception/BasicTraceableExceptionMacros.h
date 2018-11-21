#pragma once

// NOTE: make sure you include this file into .cpp ones only!

// Automatically insert debug info into exception's constructor
//#define BasicTraceableException(description, cause) \
//    BasicTraceableException(description, __FILE__, __func__, __LINE__, cause)

// Automatically insert debug info into exception's constructor
#define BasicTraceableException(description) \
    BasicTraceableException(description, __FILE__, __func__, __LINE__, \
                            std::unique_ptr<Exception::TraceableException>())
