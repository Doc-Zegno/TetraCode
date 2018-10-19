#include "IteratorExceptions.h"


namespace Handmada::TetraCode::Iterator {
    // I n v a l i d    i t e r a t o r
    InvalidIteratorException::InvalidIteratorException(const char* functionName)
        : std::runtime_error(std::string(functionName) + ": iterator is invalid")
    {
    }


    InvalidIteratorException::InvalidIteratorException(const std::string& functionName)
        : std::runtime_error(functionName + ": iterator is invalid")
    {
    }



    // C o r r u p t e d    i n p u t
    CorruptedInputSequenceException::CorruptedInputSequenceException(const char* functionName)
        : std::runtime_error(std::string(functionName) + ": corrupted input sequence")
    {
    }


    CorruptedInputSequenceException::CorruptedInputSequenceException(const std::string& functionName)
        : std::runtime_error(functionName + ": corrupted input sequence")
    {
    }
}
