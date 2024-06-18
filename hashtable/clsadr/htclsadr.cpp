namespace lasd {

//_________________________________________________________________________
//_________________________________________________________________________cnstrs & oprts

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(ulong sz) : HashTable<Data>() {
        
        htsize = minsz(sz);
        buckts = Vector<List<Data>>(minsz(sz));
    }


    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(ulong sz, const TraversableContainer<Data>& cntr) : HashTableClsAdr<Data>(std::max(sz, cntr.Size())) {
        
        cntr.Traverse([this](const Data& d) { Insert(d); });
    }


    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(ulong sz, MappableContainer<Data>&& cntr) noexcept : HashTableClsAdr<Data>(std::max(sz, cntr.Size())) {

        cntr.Map([this](Data& d) { Insert(std::move(d)); });
    }



    template <typename Data>
    HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr& ht) {
        
        HashTable<Data>::operator=(ht);
        buckts = ht.buckts;
        
        return *this;
    }


    template <typename Data>
    HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr&& ht) noexcept {

        HashTable<Data>::operator=(std::move(ht));
        std::swap(buckts, ht.buckts);
        
        return *this;
    }


    template <typename Data>
    bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr& ht) const noexcept {

        if (size != ht.size) { return false; }
        if (size == 0) { return true; }

        bool flag = true;

        buckts.Traverse([&ht, &flag](const List<Data>& lst) {
            
            lst.Traverse([&ht, &flag](const Data& d) {

                if (!ht.Exists(d)) { flag = false; }
            });
        });
            
        return flag;
    }





//_________________________________________________________________________
//_________________________________________________________________________public funs

    template <typename Data>
    bool HashTableClsAdr<Data>::Insert(const Data& d) {

        if (buckts[HashKey(d)].Insert(d)) { ++size; return true; }

        else { return false; }
    }



    template <typename Data>
    bool HashTableClsAdr<Data>::Insert(Data&& d) noexcept {

        if (buckts[HashKey(d)].Insert(std::move(d))) { ++size; return true; }

        else { return false; }
    }



    template <typename Data>
    bool HashTableClsAdr<Data>::Remove(const Data& d) {

        if (buckts[HashKey(d)].Remove(d)) { --size; return true; }

        else { return false; }
    }



    template <typename Data>
    bool HashTableClsAdr<Data>::Exists(const Data& d) const noexcept {

        return buckts[HashKey(d)].Exists(d);
    }



    template <typename Data>
    void HashTableClsAdr<Data>::Resize(ulong newSize) {

        HashTableClsAdr<Data> newHt = HashTableClsAdr<Data>(minsz(newSize));
        
        for (ulong i = 0; i < htsize; i++) {
            
            buckts[i].Traverse([&newHt](const Data& d) { newHt.Insert(d); });
        }
        
        operator=(std::move(newHt));
    }



    template <typename Data>
    void HashTableClsAdr<Data>::Clear() {

        size = 0;
        buckts = Vector<List<Data>>(htsize);
    }
}