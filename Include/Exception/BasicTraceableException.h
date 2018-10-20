#pragma once

#include <string>
#include <memory>
#include <sstream>

#include "TraceableException.h"


namespace Handmada::TetraCode::Exception {
    /// <summary>
    /// Basic implementation of <see cref="TraceableException"/>.
    /// Any other one can be implemented as an appropriate
    /// wrapper around this
    /// </summary>
    class BasicTraceableException : public TraceableException {
    private:
        std::string _description;
        std::string _fileName;
        std::string _functionName;
        int _line;
        std::unique_ptr<TraceableException> _cause;

        const char* stripFileName(const char* fileName) const;

        void appendTraceDescription(
            std::ostringstream& sout, 
            const std::string& head, 
            const TraceableException& e
        ) const;

    public:
        BasicTraceableException(
            const std::string& description,
            const std::string& fileName, 
            const std::string& functionName, 
            int line
        );

        BasicTraceableException(
            const std::string& description,
            const std::string& fileName,
            const std::string& functionName,
            int line, 
            std::unique_ptr<TraceableException>&& cause
        );

        virtual const TraceableException* cause() const override;
        virtual const std::string& fileName() const override;
        virtual const std::string& functionName() const override;
        virtual int line() const override;
        virtual std::string buildTraceString() const override;
        virtual const char* what() const override;
    };
}
