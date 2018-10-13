#pragma once

#include <memory>

#include "Types.h"
#include "Iterator.h"


namespace TetraCode {
    namespace Scrambler {
        using ByteIterator = Iterator::Iterator<byte_t>;
        using ByteIteratorPtr = std::unique_ptr<ByteIterator>;


        /// <summary>
        /// Performs specific transformations on input byte sequences.
        /// This is achieved by providing client-side classes with
        /// special encoding and decoding iterators
        /// </summary>
        class Scrambler {
        public:
            /// <summary>
            /// Build iterator to **perform** transformations during **encoding** pass
            /// on the specified input sequence
            /// </summary>
            /// <param name="iterator">Iterator over **clean** input sequence</param>
            /// <returns>Instance of **encoding** iterator</returns>
            virtual ByteIteratorPtr encodingIterator(ByteIteratorPtr&& iterator) const = 0;

            /// <summary>
            /// Build iterator to **undo** transformations during **decoding** pass
            /// on the specified input sequence
            /// </summary>
            /// <param name="iterator">Iterator over **scrambled** input sequence</param>
            /// <returns>Instance of **decoding** iterator</returns>
            virtual ByteIteratorPtr decodingIterator(ByteIteratorPtr&& iterator) const = 0;

            virtual ~Scrambler() {}
        };
    }
}