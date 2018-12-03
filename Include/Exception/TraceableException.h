#pragma once

#include <string>
#include <memory>
#include <stdexcept>


namespace Handmada::TetraCode::Exception {
    /// <summary>
    /// Interface for exceptions that can store information
    /// about the place where they were thrown and the exceptions
    /// that caused them
    /// </summary>
    class TraceableException : public std::runtime_error {
    public:
        using std::runtime_error::runtime_error;

        /// <summary>
        /// Get exception that caused this one
        /// </summary>
        /// <returns>Valid pointer to the cause or `nullptr` if there is no one</returns>
        virtual const TraceableException* cause() const = 0;

        /// <summary>
        /// Get name of file where this exception was thrown
        /// </summary>
        /// <returns>Faulted file's name</returns>
        virtual const std::string& fileName() const = 0;

        /// <summary>
        /// Get name of function that has thrown the exception
        /// </summary>
        /// <returns>Faulted function's name</returns>
        virtual const std::string& functionName() const = 0;

        /// <summary>
        /// Get the line's number of the file where this exception was thrown
        /// </summary>
        /// <returns>Faulted line's number</returns>
        virtual int line() const = 0;

        /// <summary>
        /// Get a nice formatted string that contains
        /// the trace of all exceptions in this chain.
        /// Should be used instead of <see cref="what()"/>
        /// </summary>
        /// <returns>String representation of exceptions' trace</returns>
        virtual std::string buildTraceString() const = 0;

        /// <summary>
        /// Move this exception to heap memory and wrap with `unique_ptr`
        /// </summary>
        /// <returns>`unique_ptr` to this exception</returns>
        virtual std::unique_ptr<TraceableException> move() = 0;

        /// <summary>
        /// Copy this exception to heap memory and wrap with `unique_ptr`
        /// </summary>
        /// <returns>`unique_ptr` to copy of this exception</returns>
        virtual std::unique_ptr<TraceableException> clone() const = 0;

        virtual ~TraceableException() { }
    };
}
