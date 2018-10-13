#pragma once


namespace TetraCode {
    namespace Iterator {
        /// <summary>
        /// Generic iterator interface.
        /// Iterator should be used to hide underlying container
        /// </summary>
        template<typename T>
        class Iterator {
        public:
            /// <summary>
            /// Get element this iterator is pointing to
            /// </summary>
            /// <returns>Current element</returns>
            virtual T& current() const = 0;

            /// <summary>
            /// Move this iterator to the next element in underlying container.
            /// <para>**Note:** this method must be called **before** trying to access the first element</para>
            /// </summary>
            /// <returns>`false` if there is no elements left and `true` otherwise</returns>
            virtual bool moveNext() = 0;

            virtual ~Iterator() {}
        };
    }
}