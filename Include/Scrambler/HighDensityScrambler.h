#pragma once

#include <vector>

#include "Scrambler.h"


namespace TetraCode {
    namespace Scrambler {
        class HighDensityScrambler : public Scrambler {
        private:
            class EncodingIterator : public ByteIterator {
            private:
                ByteIteratorPtr _iterator;
                byte_t _bufferedByte;
                byte_t _currentByte;
                bool _hasBuffered;

            public:
                EncodingIterator(ByteIteratorPtr&& iterator);

                virtual byte_t current() override;
                virtual bool moveNext() override;
            };

            
            class DecodingIterator : public ByteIterator {
            private:
                ByteIteratorPtr _iterator;
                byte_t _currentByte;

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