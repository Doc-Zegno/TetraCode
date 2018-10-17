#pragma once


namespace Handmada::TetraCode {
    /// <summary>
    /// Represents the version of project used for encoding
    /// </summary>
    struct Version {
        /// <summary>
        /// Major (the first) number of used version
        /// </summary>
        int major;

        /// <summary>
        /// Minor (the second) number of used version
        /// </summary>
        int minor;

        /// <summary>
        /// Micro (the third) number of used version
        /// </summary>
        int micro;

        Version(int major, int minor, int micro) : major(major), minor(minor), micro(micro) { }
    };
}