#pragma once

#include <stdexcept>
#include <string>


namespace Handmada::TetraCode::Iterator {
    /// <summary>
    /// Signalizes that instance of <see cref="Iterator"/>
    /// is being used in condition when it must not
    /// </summary>
    class InvalidIteratorException : public std::runtime_error {
    public:
        using std::runtime_error::what;

        InvalidIteratorException(const char* functionName);
        InvalidIteratorException(const std::string& functionName);
    };



    /// <summary>
    /// Signalizes that <see cref="Iterator"/> instance
    /// has failed to parse input sequence as it was corrupted
    /// </summary>
    class CorruptedInputSequenceException : public std::runtime_error {
    public:
        using std::runtime_error::what;

        CorruptedInputSequenceException(const char* functionName);
        CorruptedInputSequenceException(const std::string& functionName);
    };
}
