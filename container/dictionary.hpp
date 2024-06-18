#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP
#include "mappable.hpp"

namespace lasd {

    template <typename Data>
    class DictionaryContainer : virtual public TestableContainer<Data> {

        public:

            virtual ~DictionaryContainer() = default;

            DictionaryContainer& operator=(const DictionaryContainer&) = delete;
            DictionaryContainer& operator=(DictionaryContainer&&) noexcept = delete;

            bool operator==(const DictionaryContainer&) const noexcept = delete;
            inline bool operator!=(const DictionaryContainer&) const noexcept = delete;


            virtual bool Insert(const Data&) = 0;
            virtual bool Insert(Data&&) = 0;
            virtual bool Remove(const Data&) = 0;

            inline virtual bool InsertAll(const TraversableContainer<Data>&);
            inline virtual bool InsertAll(MappableContainer<Data>&&);
            inline virtual bool RemoveAll(const TraversableContainer<Data>&);

            inline virtual bool InsertSome(const TraversableContainer<Data>&);
            inline virtual bool InsertSome(MappableContainer<Data>&&);
            inline virtual bool RemoveSome(const TraversableContainer<Data>&);
    };
}

#include "dictionary.cpp"
#endif