#pragma once

#include <vector>

#include "Scrambler.h"


namespace Handmada::TetraCode::Sequence {
    /// <summary>
    /// Provides iterators for encoding/decoding with parity checksums
    /// </summary>
    class ParityCheckScrambler : public Scrambler {
    private:
        class EncodingIterator : public ByteIterator {
        private:
            ByteIteratorPtr _iterator;
            byte_t _current;
            byte_t _checkSum;
            int _numBytes;
            int _groupSize;
            bool _isStarted;
            bool _isValid;

        public:
            EncodingIterator(ByteIteratorPtr&& iterator, int groupSize);

            virtual byte_t current() override;
            virtual bool moveNext() override;
        };


        class DecodingIterator : public ByteIterator {
        private:
            ByteIteratorPtr _iterator;
            byte_t _current;
            std::vector<byte_t> _buffer;
            int _groupSize;
            int _index;
            bool _isValid;

        public:
            DecodingIterator(ByteIteratorPtr&& iterator);

            virtual byte_t current() override;
            virtual bool moveNext() override;
        };


        int _groupSize;

    public:
        /// <param name="groupSize">Number of bytes per one checksum</param>
        ParityCheckScrambler(int groupSize);

        /// <summary>
        /// Number of bytes that used for calculation of one checksum
        /// </summary>
        /// <returns>Number of bytes per one checksum</returns>
        int groupSize() const;

        virtual ByteIteratorPtr encodingIterator(ByteIteratorPtr&& iterator) override;
        virtual ByteIteratorPtr decodingIterator(ByteIteratorPtr&& iterator) override;

        /// <summary>
        /// Create instance of this scrambler wrapped with `unique_ptr`
        /// </summary>
        /// <param name="groupSize">Number of bytes per one checksum</param>
        /// <returns>`unique_ptr` to scrambler's instance</returns>
        static std::unique_ptr<Scrambler> create(int groupSize);
    };
}
