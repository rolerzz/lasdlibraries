#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP
#include "../hashtable.hpp"
#include "../../vector/vector.hpp"

namespace lasd {

    template <typename Data>
    class HashTableOpnAdr : virtual public HashTable<Data> {

        protected:
        
            using DictionaryContainer<Data>::size;
            using HashTable<Data>::htsize;
            using HashTable<Data>::minsz;
            using HashTable<Data>::HashKey;

            enum class state { empty, taken, cleared };
            
            Vector<Data> elements;
            Vector<state> states;
            ulong rmvdels = 0;

        public:

            HashTableOpnAdr();
            HashTableOpnAdr(ulong);

            HashTableOpnAdr(const HashTableOpnAdr& ht) { operator=(ht); };
            HashTableOpnAdr(HashTableOpnAdr&& ht) noexcept { operator=(std::move(ht)); };

            HashTableOpnAdr(ulong, const TraversableContainer<Data>&);
            HashTableOpnAdr(const TraversableContainer<Data>& cntr) : HashTableOpnAdr<Data>(cntr.Size(), cntr) {}

            HashTableOpnAdr(ulong, MappableContainer<Data>&&) noexcept;
            HashTableOpnAdr(MappableContainer<Data>&& cntr) noexcept : HashTableOpnAdr<Data>(cntr.Size(), cntr) {}

            virtual ~HashTableOpnAdr() = default;

            HashTableOpnAdr& operator=(const HashTableOpnAdr&);
            HashTableOpnAdr& operator=(HashTableOpnAdr&&) noexcept;

            bool operator==(const HashTableOpnAdr&) const noexcept;
            inline bool operator!=(const HashTableOpnAdr& ht) const noexcept { return !(operator==(ht)); }

            inline bool Insert(const Data& d) noexcept override { return Insert(d, true); }
            inline bool Insert(Data&& d) noexcept override { return Insert(d, false); }
            inline bool Remove(const Data& d) override { return Remove(d, 0); }

            inline bool Exists(const Data& d) const noexcept override { return Find(d, 0) != htsize; }
            void Resize(ulong) override;
            void Clear() override;

        protected:

            ulong Find(const Data&, ulong) const noexcept;
            bool Remove(const Data&, ulong);
            bool Insert(const Data&, bool) noexcept;
    };
}

#include "htopnadr.cpp"
#endif