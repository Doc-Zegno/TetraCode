#include "PreambleScrambler.h"
#include "CodeBits.h"


namespace Handmada::TetraCode::Scrambler {
    using Iterator::InvalidIteratorException;
    using Iterator::CorruptedInputSequenceException;


    PreambleScrambler::PreambleScrambler(const Version& hostVersion)
        : _hostVersion(hostVersion)
    {
    }


    ByteIteratorPtr PreambleScrambler::encodingIterator(ByteIteratorPtr&& iterator)
    {
        return ByteIteratorPtr(
            new EncodingIterator(_hostVersion, std::move(iterator))
        );
    }


    ByteIteratorPtr PreambleScrambler::decodingIterator(ByteIteratorPtr&& iterator)
    {
        auto it = new DecodingIterator(std::move(iterator));
        _guestVersion = it->guestVersion();
        return ByteIteratorPtr(it);
    }


    const Version& PreambleScrambler::guestVersion() const
    {
        return _guestVersion;
    }



    // H e l p e r
    union PreamblePacked {
        struct {
            unsigned length : 8;
            unsigned major : 8;
            unsigned minor : 4;
            unsigned micro : 4;
        } fields;
        byte_t raw[3];
    };



    // E n c o d i n g    I t e r a t o r
    PreambleScrambler::EncodingIterator::EncodingIterator(
        const Version& hostVersion, 
        ByteIteratorPtr&& iterator
    ) : _iterator(std::move(iterator))
    {
        auto packed = PreamblePacked();
        packed.fields.length = sizeof(packed.raw);
        packed.fields.major = hostVersion.major();
        packed.fields.minor = hostVersion.minor();
        packed.fields.micro = hostVersion.micro();
        _preamble.insert(_preamble.end(), std::begin(packed.raw), std::end(packed.raw));
        _preambleIndex = 0;

        _isValid = false;
    }


    byte_t PreambleScrambler::EncodingIterator::current() {
        if (!_isValid) {
            throw InvalidIteratorException("Preamble::EncodingIterator::current()");
        }
        return _current;
    }


    bool PreambleScrambler::EncodingIterator::moveNext() {
        _isValid = true;
        if (_preambleIndex < _preamble.size()) {
            _current = _preamble[_preambleIndex];
            _preambleIndex++;
        } else {
            if (!_iterator->moveNext()) {
                _isValid = false;
                return false;
            }
            _current = _iterator->current();
        }
        return true;
    }



    // D e c o d i n g    I t e r a t o r
    PreambleScrambler::DecodingIterator::DecodingIterator(ByteIteratorPtr&& iterator)
        : _iterator(std::move(iterator))
    {
        try {
            _isValid = false;

            auto packed = PreamblePacked();
            auto headerSize = sizeof(packed.raw);
            for (auto i = 0U; i < headerSize; i++) {
                _iterator->moveNext();
                packed.raw[i] = _iterator->current();
            }

            auto left = packed.fields.length - headerSize;
            for (auto i = 0U; i < left; i++) {
                _iterator->moveNext();
                _iterator->current();  // Trigger exception if not valid
            }

            _guestVersion = Version(packed.fields.major, packed.fields.minor, packed.fields.micro);
        } catch (std::exception&) {
            throw CorruptedInputSequenceException("Preamble::DecodingIterator::ctor()");
        }
    }


    byte_t PreambleScrambler::DecodingIterator::current() {
        if (!_isValid) {
            throw InvalidIteratorException("Preamble::DecodingIterator::current()");
        }
        return _current;
    }


    bool PreambleScrambler::DecodingIterator::moveNext() {
        if (_iterator->moveNext()) {
            _isValid = true;
            _current = _iterator->current();
            return true;
        } else {
            _isValid = false;
            return false;
        }
    }


    const Version& PreambleScrambler::DecodingIterator::guestVersion() const
    {
        return _guestVersion;
    }
}