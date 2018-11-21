#include "ParityCheckScrambler.h"

#include "IteratorExceptionsMacros.h"


namespace Handmada::TetraCode::Sequence {
    ParityCheckScrambler::ParityCheckScrambler(int groupSize)
        : _groupSize(groupSize)
    {
    }


    int ParityCheckScrambler::groupSize() const
    {
        return _groupSize;
    }


    ByteIteratorPtr ParityCheckScrambler::encodingIterator(ByteIteratorPtr&& iterator)
    {
        return ByteIteratorPtr(new EncodingIterator(std::move(iterator), _groupSize));
    }


    ByteIteratorPtr ParityCheckScrambler::decodingIterator(ByteIteratorPtr&& iterator)
    {
        return ByteIteratorPtr(new DecodingIterator(std::move(iterator)));
    }


    std::unique_ptr<Scrambler> ParityCheckScrambler::create(int groupSize)
    {
        return std::unique_ptr<Scrambler>(new ParityCheckScrambler(groupSize));
    }



    // E n c o d i n g    i t e r a t o r
    ParityCheckScrambler::EncodingIterator::EncodingIterator(
        ByteIteratorPtr&& iterator, 
        int groupSize
    ) : _iterator(std::move(iterator)), _groupSize(groupSize)
    {
        if (_groupSize > 0xFF) {
            throw TooLargeGroupSizeException(TraceableExceptionPtr(), 0xFF, _groupSize);
        }

        _checkSum = 0xFF;
        _numBytes = 0;
        _isStarted = false;
        _isValid = false;
    }


    byte_t ParityCheckScrambler::EncodingIterator::current()
    {
        if (!_isValid) {
            throw InvalidIteratorException(TraceableExceptionPtr());
        }
        return _current;
    }


    bool ParityCheckScrambler::EncodingIterator::moveNext()
    {
        _isValid = true;
        if (!_isStarted) {
            _isStarted = true;
            _current = byte_t(_groupSize);
        } else if (_numBytes == _groupSize) {
            _current = _checkSum;
            _checkSum = 0xFF;
            _numBytes = 0;
        } else {
            if (!_iterator->moveNext()) {
                _isValid = false;
            } else {
                _current = _iterator->current();
                _checkSum ^= _current;
                _numBytes++;
            }
        }
        return _isValid;
    }



    // D e c o d i n g    i t e r a t o r
    ParityCheckScrambler::DecodingIterator::DecodingIterator(ByteIteratorPtr&& iterator)
        : _iterator(std::move(iterator))
    {
        try {
            // Read group size
            _index = 0;
            _iterator->moveNext();
            _groupSize = int(_iterator->current());
            _buffer.reserve(_groupSize + 1);
            _isValid = false;
        } catch (Exception::TraceableException& e) {
            throw CorruptedInputSequenceException(e.move());
        }
    }


    byte_t ParityCheckScrambler::DecodingIterator::current()
    {
        if (!_isValid) {
            throw InvalidIteratorException(TraceableExceptionPtr());
        }
        return _current;
    }


    bool ParityCheckScrambler::DecodingIterator::moveNext()
    {
        _isValid = true;
        if (_index >= int(_buffer.size())) {
            // Buffer is exhausted
            _buffer.clear();
            _index = 0;

            for (auto i = 0; i < _groupSize + 1; i++) {
                if (_iterator->moveNext()) {
                    _buffer.push_back(_iterator->current());
                } else {
                    break;
                }
            }

            auto numBytes = int(_buffer.size());
            if (numBytes == 0) {
                // No more bytes
                _isValid = false;
                return false;
            } else if (numBytes == _groupSize + 1) {
                // Calculate and test checksum
                auto checksum = 0xFF;
                auto actual = _buffer.back();
                _buffer.pop_back();

                for (auto b : _buffer) {
                    checksum ^= b;
                }

                if (checksum != actual) {
                    throw WrongChecksumException(TraceableExceptionPtr(), checksum, actual);
                }
            }
        }

        _current = _buffer[_index];
        _index++;
        return true;
    }
}
