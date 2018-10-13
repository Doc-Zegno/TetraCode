#include "HighDensityScrambler.h"


namespace TetraCode {
    namespace Scrambler {
        ByteIteratorPtr HighDensityScrambler::encodingIterator(ByteIteratorPtr&& iterator) const
        {
            return ByteIteratorPtr(new HighDensityScrambler::EncodingIterator(std::move(iterator)));
        }


        ByteIteratorPtr HighDensityScrambler::decodingIterator(ByteIteratorPtr&& iterator) const
        {
            throw std::runtime_error("HD-Scrambler::decodingIterator(): not implemented");
            return ByteIteratorPtr();
        }


        // E n c o d i n g    I t e r a t o r
        const byte_t ESCAPE_BITS = 0b10101111;


        HighDensityScrambler::EncodingIterator::EncodingIterator(ByteIteratorPtr&& iterator)
            : _iterator(std::move(iterator))
        {
            _hasBuffered = true;
            _bufferedByte = ESCAPE_BITS;
        }


        byte_t HighDensityScrambler::EncodingIterator::current()
        {
            return _currentByte;
        }


        bool HighDensityScrambler::EncodingIterator::moveNext()
        {
            if (_hasBuffered) {
                _hasBuffered = false;
                _currentByte = _bufferedByte;
            } else {
                if (!_iterator->moveNext()) {
                    return false;
                }

                auto current = _iterator->current();
                auto activeMask = current & 0b00001111;
                if (activeMask == 0 || (activeMask & (activeMask - 1)) == 0 || current == ESCAPE_BITS) {
                    _hasBuffered = true;
                    _bufferedByte = ~current;
                    _currentByte = ESCAPE_BITS;
                } else {
                    _currentByte = current;
                }
            }

            return true;
        }
    }
}
