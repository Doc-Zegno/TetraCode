#include "BasicTraceableException.h"

#include <sstream>


namespace Handmada::TetraCode::Exception {
    BasicTraceableException::BasicTraceableException(
        const std::string& description,
        const std::string& fileName, 
        const std::string& functionName, 
        int line
    ) : BasicTraceableException(
            description, 
            fileName, 
            functionName, 
            line,
            std::unique_ptr<TraceableException>()
        )
    {
    }


    BasicTraceableException::BasicTraceableException(
        const std::string& description,
        const std::string& fileName,
        const std::string& functionName,
        int line,
        std::unique_ptr<TraceableException>&& cause
    ) : _description(description), 
        _fileName(fileName), 
        _functionName(functionName), 
        _line(line), 
        _cause(std::move(cause))
    {
    }


    const TraceableException* BasicTraceableException::cause() const
    {
        return _cause.get();
    }


    const std::string& BasicTraceableException::fileName() const
    {
        return _fileName;
    }


    const std::string& BasicTraceableException::functionName() const
    {
        return _functionName;
    }


    int BasicTraceableException::line() const
    {
        return _line;
    }


    const char* BasicTraceableException::stripFileName(const char* fileName) const
    {
        auto lastName = fileName;
        for (auto p = fileName; p; p++) {
            if (*p == '/' || *p == '\\') {
                lastName = p + 1;
            }
        }
        return lastName;
    }


    void BasicTraceableException::appendTraceDescription(
        std::ostringstream& sout, 
        const std::string& head, 
        const TraceableException& e
    ) const
    {
        sout << '\t' << head << ": ";
        sout << stripFileName(e.fileName().c_str()) << ':' << e.line();
        sout << " at " << e.functionName();
        sout << "(): " << e.what() << '\n';
    }


    std::string BasicTraceableException::buildTraceString() const
    {
        auto sout = std::ostringstream();
        sout << "TraceableException instance was thrown:\n";
        appendTraceDescription(sout, "top-level", *this);
        for (const TraceableException* cause = _cause.get(); cause; cause = cause->cause()) {
            appendTraceDescription(sout, "caused by", *cause);
        }
        return sout.str();
    }


    const char* BasicTraceableException::what() const
    {
        return _description.c_str();
    }
}
