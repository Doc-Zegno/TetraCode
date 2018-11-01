#pragma once

#include <vector>
#include <stack>

#include "Scrambler.h"


namespace Handmada::TetraCode::Sequence {
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
            std::stack<byte_t, std::vector<byte_t>> _buffer;
            byte_t _currentByte;
            bool _isValid;

        public:
            EncodingIterator(ByteIteratorPtr&& iterator, int padding);

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


        int _padding;

    public:
        /// <param name="padding">Number of padding bytes to be inserted</param>
        HighDensityScrambler(int padding);

        virtual ByteIteratorPtr encodingIterator(ByteIteratorPtr&& iterator) override;
        virtual ByteIteratorPtr decodingIterator(ByteIteratorPtr&& iterator) override;
    };
}
