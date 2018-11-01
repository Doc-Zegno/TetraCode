#pragma once

#include <string>
#include <sstream>
#include <cstring>
#include <type_traits>

#include "BasicTraceableException.h"


namespace Handmada::TetraCode {
    /// <summary>
    /// Provides functionality for building formatted strings
    /// </summary>
    class Format {
    private:
        template<typename T>
        static void inject(std::ostream& out, const T& value, const char* options)
        {
            if (*options == '\0') {
                out << value;
            } else {
                if (!strcmp(options, ":x")) {
                    // Hex
                    if constexpr (std::is_integral<T>::value) {
                        out << std::hex;
                        out << value;
                        out << std::dec;
                    } else {
                        throw Exception::BasicTraceableException(
                            "\":x\" option is not compatible with non-integral type",
                            __FILE__,
                            __func__,
                            __LINE__,
                            std::unique_ptr<Exception::TraceableException>()
                        );
                    }
                } else {
                    // Unknown option
                    throw Exception::BasicTraceableException(
                        std::string("unrecognized options \"") + options + "\"",
                        __FILE__,
                        __func__,
                        __LINE__,
                        std::unique_ptr<Exception::TraceableException>()
                    );
                }
            }
        }


        template<typename T, typename... TArgs>
        static void step(std::ostream& out, char* format, const T& value, const TArgs&... args)
        {
            auto p = std::strchr(format, '{');
            if (!p) {
                throw Exception::BasicTraceableException(
                    "placeholder {} wasn't found",
                    __FILE__,
                    __func__,
                    __LINE__,
                    std::unique_ptr<Exception::TraceableException>()
                );
            }

            auto q = std::strchr(p + 1, '}');
            if (!q) {
                throw Exception::BasicTraceableException(
                    "closing braces } weren't found",
                    __FILE__,
                    __func__,
                    __LINE__,
                    std::unique_ptr<Exception::TraceableException>()
                );
            }

            *p = '\0';
            *q = '\0';
            out << format;
            inject(out, value, p + 1);

            step(out, q + 1, args...);
        }


        static void step(std::ostream& out, char* format)
        {
            auto p = std::strchr(format, '{');
            if (p) {
                throw Exception::BasicTraceableException(
                    "opening braces { were found but no arguments were provided",
                    __FILE__,
                    __func__,
                    __LINE__,
                    std::unique_ptr<Exception::TraceableException>()
                );
            }
            out << format;
        }

    public:
        /// <summary>
        /// Build string using specified format and input values.
        /// <para>**Example**: format "({}, {}, {})" and values 1, 2, 3 will produce
        /// "(1, 2, 3)"</para>
        /// <para>**Note**: use {:x} for hex</para>
        /// </summary>
        /// <param name="format">Pattern of string to be built</param>
        /// <param name="args">Values to be injected in output string</param>
        /// <returns>Copy of format string with injected values</returns>
        template<typename... TArgs>
        static std::string str(const std::string& format, const TArgs&... args)
        {
            try {
                auto sout = std::ostringstream();
                auto size = format.size() + 1;
                auto buffer = std::unique_ptr<char[]>(new char[size]);
                std::memcpy(buffer.get(), format.c_str(), size);
                step(sout, buffer.get(), args...);
                return sout.str();
            } catch (Exception::TraceableException& e) {
                throw Exception::BasicTraceableException(
                    std::string("unable to build string with format:\n\t\t\"")
                    + format + "\"",
                    __FILE__,
                    __func__,
                    __LINE__,
                    e.move()
                );
            }
        }
    };
}