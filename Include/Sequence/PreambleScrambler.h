#pragma once

#include <vector>

#include "Version.h"
#include "Scrambler.h"


namespace Handmada::TetraCode::Sequence {
    /// <summary>
    /// Concatenates byte representation of TetraCode preamble
    /// (contains encoding system version)
    /// with input byte sequence during encoding pass.
    /// Reads and removes preamble from byte sequence during decoding pass
    /// </summary>
    class PreambleScrambler : public Scrambler {
    private:
        class EncodingIterator : public ByteIterator {
        private:
            std::vector<byte_t> _preamble;
            size_t _preambleIndex;
            ByteIteratorPtr _iterator;
            byte_t _current;
            bool _isValid;

        public:
            EncodingIterator(const Version& hostVersion, ByteIteratorPtr&& iterator);

            virtual byte_t current() override;
            virtual bool moveNext() override;
        };


        class DecodingIterator : public ByteIterator {
        private:
            Version _guestVersion;
            ByteIteratorPtr _iterator;
            byte_t _current;
            bool _isValid;

        public:
            DecodingIterator(ByteIteratorPtr&& iterator);

            virtual byte_t current() override;
            virtual bool moveNext() override;

            const Version& guestVersion() const;
        };


        Version _hostVersion;
        Version _guestVersion;

    public:
        /// <param name="hostVersion">Version of host encoding system</param>
        PreambleScrambler(const Version& hostVersion);

        virtual ByteIteratorPtr encodingIterator(ByteIteratorPtr&& iterator) override;
        virtual ByteIteratorPtr decodingIterator(ByteIteratorPtr&& iterator) override;

        /// <summary>
        /// Get guest version for the last decoded sequence
        /// </summary>
        /// <returns>Last guest version</returns>
        const Version& guestVersion() const;

        /// <summary>
        /// Create scrambler's instance wrapped with `unique_ptr`
        /// </summary>
        /// <param name="hostVersion">Version of host encoding system</param>
        /// <returns>`unique_ptr` to scrambler's instance</returns>
        static std::unique_ptr<Scrambler> create(const Version& hostVersion);
    };
}
