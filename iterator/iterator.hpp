#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace lasd {

    template <typename Data>
    class Iterator {

        public:

            Iterator() = default;
            Iterator(const Iterator&) = default;
            Iterator(Iterator&&) = default;
            virtual ~Iterator() = default;

            Iterator& operator=(const Iterator&) = delete;
            Iterator& operator=(Iterator&&) = delete;
            
            bool operator==(const Iterator&) const = delete;
            inline bool operator!=(const Iterator&) const = delete;

            virtual const Data& operator*() const = 0;
            virtual bool Terminated() const noexcept = 0;
    };





    template <typename Data>
    class MutableIterator : virtual public Iterator<Data> {

        protected: using Iterator<Data>::operator*;

        public:

            MutableIterator() = default;
            MutableIterator(const MutableIterator&) = default;
            MutableIterator(MutableIterator&&) = default;
            virtual ~MutableIterator() = default;

            MutableIterator& operator=(const MutableIterator&) = delete;
            MutableIterator& operator=(MutableIterator&&) = delete;

            bool operator==(const MutableIterator&) const = delete;
            inline bool operator!=(const MutableIterator&) const = delete;

            virtual Data& operator*() = 0;
    };





    template <typename Data>
    class ForwardIterator : virtual public Iterator<Data> {

        public:

            virtual ~ForwardIterator() = default;

            ForwardIterator& operator=(const ForwardIterator&) = delete;
            ForwardIterator& operator=(ForwardIterator&&) = delete;

            bool operator==(const ForwardIterator&) const = delete;
            inline bool operator!=(const ForwardIterator&) const = delete;

            virtual ForwardIterator& operator++() = 0;
    };





    template <typename Data>
    class ResettableIterator : virtual public Iterator<Data> {

        public:

            virtual ~ResettableIterator() = default;
        
            ResettableIterator& operator=(const ResettableIterator&) = delete;
            ResettableIterator& operator=(ResettableIterator&&) = delete;

            bool operator==(const ResettableIterator&) const = delete;
            inline bool operator!=(const ResettableIterator&) const = delete;

            virtual void Reset() noexcept = 0;
    };
}

#endif