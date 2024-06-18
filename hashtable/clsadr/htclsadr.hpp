#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP
#include "../hashtable.hpp"
#include "../../vector/vector.hpp"
#include "../../list/list.hpp"

namespace lasd {

    template <typename Data>
    class HashTableClsAdr : virtual public HashTable<Data> {

        protected:

            using DictionaryContainer<Data>::size;
            using HashTable<Data>::htsize;
            using HashTable<Data>::minsz;
            using HashTable<Data>::HashKey;
            
            Vector<List<Data>> buckts;

        public:

            HashTableClsAdr() : HashTable<Data>() { buckts = Vector<List<Data>>(defaultSize); }
            HashTableClsAdr(ulong);

            HashTableClsAdr(const HashTableClsAdr& ht) { operator=(ht); }
            HashTableClsAdr(HashTableClsAdr&& ht) noexcept { operator=(std::move(ht)); }

            HashTableClsAdr(ulong, const TraversableContainer<Data>&);
            HashTableClsAdr(const TraversableContainer<Data>& cntr) : HashTableClsAdr<Data>(cntr.Size(), cntr) {}

            HashTableClsAdr(ulong, MappableContainer<Data>&&) noexcept;
            HashTableClsAdr(MappableContainer<Data>&& cntr) noexcept : HashTableClsAdr<Data>(cntr.Size(), cntr) {}

            virtual ~HashTableClsAdr() = default;

            HashTableClsAdr& operator=(const HashTableClsAdr&);
            HashTableClsAdr& operator=(HashTableClsAdr&&) noexcept;

            bool operator==(const HashTableClsAdr&) const noexcept;
            inline bool operator!=(const HashTableClsAdr& ht) const noexcept { return !(operator==(ht)); }

            bool Insert(const Data&) override;
            bool Insert(Data&&) noexcept override;
            bool Remove(const Data&) override;

            bool Exists(const Data&) const noexcept override;
            void Resize(ulong) override;
            void Clear() override;
    };
}

#include "htclsadr.cpp"
#endif