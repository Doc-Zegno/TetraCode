#pragma once

#include <string>
#include <exception>


namespace Handmada::TetraCode::Exception {
    /// <summary>
    /// Interface for exceptions that can store information
    /// about the place where they were thrown and the exceptions
    /// that caused them
    /// </summary>
    class TraceableException : public std::exception {
    public:
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
        /// Get a short description of this exception.
        /// You shouldn't assume that this method will return
        /// any info about this exception's cause chain
        /// since it's here for back compability purposes only
        /// and effectively is a useless shit.
        /// For tracing use <see cref="buildTraceString()"/>
        /// or <see cref="cause()"/> methods instead
        /// </summary>
        /// <returns>This exception's description</returns>
        virtual const char* what() const override = 0;

        virtual ~TraceableException() { }
    };
}
