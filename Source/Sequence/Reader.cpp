#include "Reader.h"

#include "UtilFunctions.h"
#include "IteratorExceptionsMacros.h"


namespace Handmada::TetraCode::Sequence {
    const auto BUFFER_SIZE = 256;


    // H e l p e r
    class ReadingIterator : public Iterator<byte_t> {
    private:
        IO::InputStream& _stream;
        byte_t _buffer[BUFFER_SIZE];
        int _size;
        int _index;

    public:
        ReadingIterator(IO::InputStream& in);

        virtual byte_t current() override;
        virtual bool moveNext() override;
    };


    ReadingIterator::ReadingIterator(IO::InputStream& stream)
        : _stream(stream)
    {
        _index = -1;
        _size = 0;
    }


    byte_t ReadingIterator::current()
    {
        if (!isInRange(_index, _size)) {
            throw InvalidIteratorException(TraceableExceptionPtr());
        }
        return _buffer[_index];
    }

    
    bool ReadingIterator::moveNext()
    {
        if (_index < _size - 1) {
            _index++;
            return true;
        } else {
            // Try read from stream
            _size = _stream.read(_buffer, BUFFER_SIZE);
            _index = 0;
            return _size > 0;
        }
    }



    // F u n c t i o n s
    std::unique_ptr<Iterator<byte_t>> readSequence(IO::InputStream& stream)
    {
        return std::unique_ptr<Iterator<byte_t>>(new ReadingIterator(stream));
    }
}
