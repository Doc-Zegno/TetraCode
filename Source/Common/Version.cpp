#include "Version.h"


namespace Handmada::TetraCode {
    Version::Version(int major, int minor, int micro)
        : _major(major), _minor(minor), _micro(micro)
    {
    }


    int Version::major() const
    {
        return _major;
    }


    int Version::minor() const
    {
        return _minor;
    }


    int Version::micro() const
    {
        return _micro;
    }


    std::string Version::toString() const
    {
        auto majorStr = std::to_string(_major);
        auto minorStr = std::to_string(_minor);
        auto microStr = std::to_string(_micro);
        return majorStr + "." + minorStr + "." + microStr;
    }


    bool Version::isCompatible(const Version& version) const
    {
        return _major == version._major && _minor == version._minor;
    }


    bool Version::operator==(const Version& version) const
    {
        return _major == version._major && _minor == version._minor && _micro == version._micro;
    }


    bool Version::operator!=(const Version& version) const
    {
        return !(operator==(version));
    }
}