#pragma once

#include <memory>

#include "Iterator.h"


namespace Handmada::TetraCode::Iterator {
    /// <summary>
    /// Basic implementation of <see cref="Iterator"/> over raw array
    /// </summary>
    template<typename T>
    class BasicIterator : public Iterator<T> {
    private:
        T * _current;
        T* _last;
        bool _isValid;

    public:
        BasicIterator(T* start, T* end);

        virtual T current() override;
        virtual bool moveNext() override;

        /// <summary>
        /// Create iterator's instance wrapped by `unique_ptr`
        /// </summary>
        /// <param name="start">Pointer to the start of underlying array</param>
        /// <param name="end">Pointer to the end of underlying array</param>
        /// <returns>Iterator's instance</returns>
        static std::unique_ptr<Iterator<T>> create(T* start, T* end);
    };


    template<typename T>
    inline BasicIterator<T>::BasicIterator(T* start, T* end)
        : _current(start - 1), _last(end - 1), _isValid(false)
    {
    }


    template<typename T>
    inline T BasicIterator<T>::current()
    {
        if (!_isValid) {
            throw InvalidIteratorException("BasicIterator::current()");
        }
        return *_current;
    }


    template<typename T>
    inline bool BasicIterator<T>::moveNext()
    {
        _isValid = true;  // Make valid after first call
        _current++;
        if (_current > _last) {
            _isValid = false;
            _current = _last;
            return false;
        } else {
            return true;
        }
    }


    template<typename T>
    inline std::unique_ptr<Iterator<T>> BasicIterator<T>::create(T* start, T* end)
    {
        return std::unique_ptr<Iterator<T>>(new BasicIterator(start, end));
    }
}
