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
        InvalidIteratorException(const char* functionName);
        InvalidIteratorException(const std::string& functionName);

        virtual const char* what() const override;
    };
}
