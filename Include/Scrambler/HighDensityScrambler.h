#pragma once

#include <vector>

#include "Scrambler.h"


namespace TetraCode {
    namespace Scrambler {
        /// <summary>
        /// Increases the *density* of input sequence in such a way
        /// that output bytes code instances of <see cref="TetraTree"/>
        /// with at least 2 active children 
        /// </summary>
        class HighDensityScrambler : public Scrambler {
        private:
            class EncodingIterator : public ByteIterator {
            private:
                ByteIteratorPtr _iterator;
                byte_t _bufferedByte;
                byte_t _currentByte;
                bool _hasBuffered;
                bool _isValid;

            public:
                EncodingIterator(ByteIteratorPtr&& iterator);

                virtual byte_t current() override;
                virtual bool moveNext() override;
            };

            
            class DecodingIterator : public ByteIterator {
            private:
                ByteIteratorPtr _iterator;
                byte_t _currentByte;
                bool _isValid;

            public:
                DecodingIterator(ByteIteratorPtr&& iterator);

                virtual byte_t current() override;
                virtual bool moveNext() override;
            };


        public:
            HighDensityScrambler() {};

            virtual ByteIteratorPtr encodingIterator(ByteIteratorPtr&& iterator) const override;
            virtual ByteIteratorPtr decodingIterator(ByteIteratorPtr&& iterator) const override;
        };
    }
}