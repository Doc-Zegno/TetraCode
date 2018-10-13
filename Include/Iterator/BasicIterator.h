#pragma once

#include "Iterator.h"


namespace TetraCode {
    namespace Iterator {
        /// <summary>
        /// Basic implementation of <see cref="Iterator"/> over raw array
        /// </summary>
        template<typename T>
        class BasicIterator : public Iterator<T> {
        private:
            T * _current;
            T* _last;

        public:
            BasicIterator(T* start, T* end);

            virtual T& current() const override;
            virtual bool moveNext() override;
        };


        template<typename T>
        inline BasicIterator<T>::BasicIterator(T* start, T* end)
            : _current(start - 1), _last(end - 1)
        {
        }


        template<typename T>
        inline T& BasicIterator<T>::current() const
        {
            return *_current;
        }


        template<typename T>
        inline bool BasicIterator<T>::moveNext()
        {
            _current++;
            if (_current > _last) {
                _current = _last;
                return false;
            } else {
                return true;
            }
        }
    }
}