#include "Pixel.h"

#include <cstdlib>
#include <cstring>

#include "UtilFunctions.h"
#include "BasicTraceableException.h"
#include "BasicTraceableExceptionMacros.h"


namespace Handmada::TetraCode::Visual {
    using TraceableExceptionPtr = std::unique_ptr<Exception::TraceableException>;


    Pixel::Pixel(const char* hexCode) : Pixel(std::string(hexCode))
    {
    }


    Pixel::Pixel(const std::string& hexCode)
    {
        if (hexCode.size() != 7 || hexCode[0] != '#') {
            throw Exception::BasicTraceableException(
                std::string("invalid hex string: ") + hexCode
            );
        }

        auto str = hexCode.c_str() + 1;
        for (auto i = 0; i < 3; i++) {
            char buffer[3] = { 0 };
            buffer[0] = str[0];
            buffer[1] = str[1];
            str += 2;
            
            char* endptr;
            _channels[i] = byte_t(strtol(buffer, &endptr, 16));
            
            if (*endptr != '\0') {
                const char* channelStrs[] = {
                    "R",
                    "G",
                    "B"
                };
                throw Exception::BasicTraceableException(
                    std::string("invalid hex for ") + channelStrs[i] + " channel: " + hexCode
                );
            }
        }
    }


    Pixel::Pixel(byte_t r, byte_t g, byte_t b)
    {
        _channels[0] = r;
        _channels[1] = g;
        _channels[2] = b;
    }


    byte_t Pixel::r() const
    {
        return _channels[0];
    }


    byte_t Pixel::g() const
    {
        return _channels[1];
    }


    byte_t Pixel::b() const
    {
        return _channels[2];
    }


    byte_t Pixel::operator[](int channel) const
    {
        if (!isInRange(channel, 3)) {
            auto indexStr = std::to_string(channel);
            throw Exception::BasicTraceableException(
                std::string("index out of range: ") + indexStr
            );
        }

        return _channels[channel];
    }


    std::string Pixel::toString() const
    {
        char buffer[10] = { 0 };
        auto r = _channels[0];
        auto g = _channels[1];
        auto b = _channels[2];
        snprintf(buffer, 9, "#%02hhx%02hhx%02hhx", r, g, b);
        return std::string(buffer);
    }


    bool Pixel::operator==(const Pixel& p) const
    {
        return std::memcmp(_channels, p._channels, 3) == 0;
    }


    bool Pixel::operator!=(const Pixel& p) const
    {
        return !(operator==(p));
    }
}
