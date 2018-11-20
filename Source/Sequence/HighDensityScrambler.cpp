#include "HighDensityScrambler.h"
#include "IteratorExceptionsMacros.h"
#include "CodeBits.h"


namespace Handmada::TetraCode::Sequence {
    using Exception::TraceableException;


    HighDensityScrambler::HighDensityScrambler(int padding)
        : _padding(padding)
    {
    }


    ByteIteratorPtr HighDensityScrambler::encodingIterator(ByteIteratorPtr&& iterator)
    {
        return ByteIteratorPtr(
            new HighDensityScrambler::EncodingIterator(std::move(iterator), _padding)
        );
    }


    ByteIteratorPtr HighDensityScrambler::decodingIterator(ByteIteratorPtr&& iterator)
    {
        return ByteIteratorPtr(
            new HighDensityScrambler::DecodingIterator(std::move(iterator))
        );
    }


    std::unique_ptr<Scrambler> HighDensityScrambler::create(int padding)
    {
        return std::unique_ptr<Scrambler>(new HighDensityScrambler(padding));
    }



    // E n c o d i n g    I t e r a t o r
    constexpr byte_t ESCAPE_BITS = Code::CodeBits::escapeBits();


    HighDensityScrambler::EncodingIterator::EncodingIterator(ByteIteratorPtr&& iterator, int padding)
        : _iterator(std::move(iterator))
    {
        auto maximumPadding = Code::CodeBits::maxSmallInt();
        if (padding > maximumPadding) {
            throw TooLargePaddingException(TraceableExceptionPtr(), maximumPadding, padding);
        }

        // Force iterator to use padding bits at first steps
        for (auto i = 0; i <= padding; i++) {
            _buffer.push(Code::CodeBits::packSmallInt(i));
        }
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
        if (!_buffer.empty()) {
            _currentByte = _buffer.top();
            _buffer.pop();
        } else {
            if (!_iterator->moveNext()) {
                _isValid = false;
                return false;
            }

            auto current = _iterator->current();
            auto numActives = Code::CodeBits(current).numActives();

            // Escape "low density" and special bytes
            if (numActives < 2 || current == ESCAPE_BITS) {
                _buffer.push(~current);
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
            _iterator->moveNext();
            auto current = _iterator->current();
            auto numLeft = Code::CodeBits::unpackSmallInt(current);

            // Read padding bytes
            for (; numLeft > 0; numLeft--) {
                _iterator->moveNext();
                current = _iterator->current();
                auto actual = Code::CodeBits::unpackSmallInt(current);
                auto expected = numLeft - 1;
                if (actual != expected) {
                    throw CorruptedPaddingException(TraceableExceptionPtr(), expected, actual);
                }
            }

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
