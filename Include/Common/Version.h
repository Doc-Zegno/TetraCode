#pragma once

#include <string>


namespace Handmada::TetraCode {
    /// <summary>
    /// Represents the version of project used for encoding
    /// </summary>
    class Version {
    private:
        int _major;
        int _minor;
        int _micro;

    public:
        Version() = default;
        Version(int major, int minor, int micro);

        /// <summary>
        /// Major (the first) number of used version
        /// </summary>
        int major() const;

        /// <summary>
        /// Minor (the second) number of used version
        /// </summary>
        int minor() const;

        /// <summary>
        /// Micro (the third) number of used version
        /// </summary>
        int micro() const;

        /// <summary>
        /// Get string representation of version
        /// </summary>
        /// <returns>String representation</returns>
        std::string toString() const;

        /// <summary>
        /// Check whether this version is compatible with a specified one
        /// </summary>
        /// <param name="version">Version to be compared to</param>
        /// <returns>`true` if versions are compatible and `false` otherwise</returns>
        bool isCompatible(const Version& version) const;

        bool operator==(const Version& version) const;
        bool operator!=(const Version& version) const;
    };
}