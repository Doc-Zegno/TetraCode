#include "IteratorExceptions.h"


namespace TetraCode {
    namespace Iterator {
        InvalidIteratorException::InvalidIteratorException(const char* functionName)
            : std::runtime_error(std::string(functionName) + ": iterator is invalid")
        {
        }


        InvalidIteratorException::InvalidIteratorException(const std::string& functionName)
            : std::runtime_error(functionName + ": iterator is invalid")
        {
        }


        const char* InvalidIteratorException::what() const
        {
            return std::runtime_error::what();
        }
    }
}