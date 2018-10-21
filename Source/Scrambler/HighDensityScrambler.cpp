#include "HighDensityScrambler.h"
#include "IteratorExceptionsMacros.h"
#include "CodeBits.h"


namespace Handmada::TetraCode::Scrambler {
    using Exception::TraceableException;
    using Iterator::InvalidIteratorException;
    using Iterator::CorruptedInputSequenceException;
    using Iterator::TraceableExceptionPtr;


    ByteIteratorPtr HighDensityScrambler::encodingIterator(ByteIteratorPtr&& iterator)
    {
        return ByteIteratorPtr(new HighDensityScrambler::EncodingIterator(std::move(iterator)));
    }


    ByteIteratorPtr HighDensityScrambler::decodingIterator(ByteIteratorPtr&& iterator)
    {
        return ByteIteratorPtr(new HighDensityScrambler::DecodingIterator(std::move(iterator)));
    }


    // E n c o d i n g    I t e r a t o r
    constexpr byte_t ESCAPE_BITS = Code::CodeBits::escapeBits();


    HighDensityScrambler::EncodingIterator::EncodingIterator(ByteIteratorPtr&& iterator)
        : _iterator(std::move(iterator))
    {
        // Force iterator to use ESCAPE_BITS as the first output byte
        _hasBuffered = true;
        _bufferedByte = ESCAPE_BITS;
        _isValid = false;
    }


    byte_t HighDensityScrambler::EncodingIterator::current()
    {
        if (!_isValid) {
            throw InvalidIteratorException(TraceableExceptionPtr());
        }
        return _currentByte;
    }


    bool HighDensityScrambler::EncodingIterator::moveNext()
    {
        _isValid = true;
        if (_hasBuffered) {
            _hasBuffered = false;
            _currentByte = _bufferedByte;
        } else {
            if (!_iterator->moveNext()) {
                _isValid = false;
                return false;
            }

            auto current = _iterator->current();
            auto numActives = Code::CodeBits(current).numActives();

            // Escape "low density" and special bytes
            if (numActives < 2 || current == ESCAPE_BITS) {
                _hasBuffered = true;
                _bufferedByte = ~current;
                _currentByte = ESCAPE_BITS;
            } else {
                _currentByte = current;
            }
        }

        return true;
    }


    // D e c o d i n g    i t e r a t o r
    HighDensityScrambler::DecodingIterator::DecodingIterator(ByteIteratorPtr&& iterator)
        : _iterator(std::move(iterator))
    {
        try {
            // Ignore the first escape byte
            _iterator->moveNext();
            _iterator->current();  // Trigger exception if failed
            _isValid = false;
        } catch (TraceableException& e) {
            throw CorruptedInputSequenceException(e.move());
        } 
    }


    byte_t HighDensityScrambler::DecodingIterator::current()
    {
        if (!_isValid) {
            throw InvalidIteratorException(TraceableExceptionPtr());
        }
        return _currentByte;
    }


    bool HighDensityScrambler::DecodingIterator::moveNext()
    {
        if (!_iterator->moveNext()) {
            _isValid = false;
            return false;
        }

        _isValid = true;
        auto current = _iterator->current();
        if (current == ESCAPE_BITS) {
            try {
                _iterator->moveNext();
                current = ~_iterator->current();
            } catch (TraceableException& e) {
                throw CorruptedInputSequenceException(e.move());
            }
        }

        _currentByte = current;
        return true;
    }
}
