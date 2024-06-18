#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include "../container/dictionary.hpp"
#define defaultSize 128UL

namespace lasd {

    template <typename Data>
    class Hashable {

        public: ulong operator()(const Data& d) const noexcept = 0;
    };





    template <typename Data>
    class HashTable :
        virtual public ResizableContainer,
        virtual public DictionaryContainer<Data> {
    
        protected:

            using DictionaryContainer<Data>::size;
            static const Hashable<Data> encash;
            static const ulong prime = 1000000016531;
            ulong htsize = defaultSize;
            ulong acff = 1;
            ulong bcff = 0;

            HashTable() { size = 0; setRandCff(); }
            
            HashTable(const HashTable& ht) { operator=(ht); }
            HashTable(HashTable&& ht) noexcept { operator=(std::move(ht)); }

            HashTable& operator=(const HashTable&);
            HashTable& operator=(HashTable&&) noexcept;

        public:
        
            virtual ~HashTable() = default;

            bool operator==(const HashTable&) const noexcept = delete;
            inline bool operator!=(const HashTable&) const noexcept = delete;

        protected:

            inline ulong minsz(ulong sz) noexcept { return std::max(defaultSize, rup2(sz)); }
            virtual ulong HashKey(const Data&) const noexcept;
            void setRandCff();
            ulong rup2(ulong) noexcept;
    };
}

#include "hashtable.cpp"
#endif