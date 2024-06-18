namespace lasd {

//_________________________________________________________________________
//_________________________________________________________________________cnstrs & oprts

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr() : HashTable<Data>() {

        elements = Vector<Data>(defaultSize);
        states = Vector<state>(defaultSize);
        
        for (ulong i = 0; i < htsize; i++) { states[i] = state::empty; }
    }



    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(ulong sz) : HashTable<Data>() {

        htsize = minsz(sz);
        elements = Vector<Data>(minsz(sz));
        states = Vector<state>(minsz(sz));
        
        for (ulong i = 0; i < htsize; i++) { states[i] = state::empty; }
    }



    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(ulong sz, const TraversableContainer<Data>& cntr) : HashTableOpnAdr<Data>(std::max(sz, cntr.Size())) {
        
        cntr.Traverse([this](const Data& d) { Insert(d); });
    }



    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(ulong sz, MappableContainer<Data>&& cntr) noexcept : HashTableOpnAdr<Data>(std::max(sz, cntr.Size())) {

        cntr.Map([this](Data& d) { Insert(std::move(d)); });
    }



    template <typename Data>
    HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr& ht) {

        HashTable<Data>::operator=(ht);
        elements = ht.elements;
        states = ht.states;

        return *this;
    }



    template <typename Data>
    HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr&& ht) noexcept {

        HashTable<Data>::operator=(std::move(ht));
        std::swap(elements, ht.elements);
        std::swap(states, ht.states);
        
        return *this;
    }



    template <typename Data>
    bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr& ht) const noexcept {

        if (size != ht.size) { return false; }
        if (size == 0) { return true; }

        for (ulong i = 0; i < htsize; i++) {

            if ((states[i] == state::taken) && (!ht.Exists(elements[i]))) { return false; }
        }

        return true;
    }





//_________________________________________________________________________
//_________________________________________________________________________public funs

    template <typename Data>
    void HashTableOpnAdr<Data>::Resize(ulong newsz) {

        HashTableOpnAdr<Data> newHt = HashTableOpnAdr<Data>(minsz(newsz));

        for (ulong i = 0; i < htsize; i++) {
            
            if (states[i] == state::taken) { newHt.Insert(elements[i]); }
        }
        
        operator=(std::move(newHt));
    }



    template <typename Data>
    void HashTableOpnAdr<Data>::Clear() {

        size = 0;
        elements = Vector<Data>(htsize);
        states = Vector<state>(htsize);
        states.Map([](state& s){ s = state::empty; }); 
    }





//_________________________________________________________________________
//_________________________________________________________________________protected funs

    template <typename Data>
    ulong HashTableOpnAdr<Data>::Find(const Data& d, ulong iter) const noexcept {

        ulong encd = HashKey(d);
        ulong srcidx = encd;

        for (ulong i = iter; i < htsize; i++) {

            srcidx = (encd + (i * i + i) / 2) % htsize;
            
            if (states[srcidx] == state::cleared && elements[srcidx] == d) { break; }
            
            if (states[srcidx] == state::taken && elements[srcidx] == d) { return srcidx; }
            
            if (states[srcidx] == state::empty) { break; }
        }

        return htsize;
    }



    template <typename Data>
    bool HashTableOpnAdr<Data>::Remove(const Data& d, ulong i) {

        ulong rmvidx = Find(d, i);
        
        if (rmvidx != htsize) {
            
            states[rmvidx] = state::cleared;
            --size;

            if (++rmvdels > htsize * 0.3) { Resize(htsize); }
            return true;
        
        } else { return false; }
    }



    template <typename Data>
    bool HashTableOpnAdr<Data>::Insert(const Data& d, bool copy) noexcept {
                
        if (size > htsize / 2) { Resize(htsize * 2); }
        
        ulong encd = HashKey(d);
        ulong idx = encd;
        ulong i = 0;
        
        while (i < htsize && states[idx] == state::taken) {
            
            if (elements[idx] == d) { return false; }

            ++i;
            idx = (encd + (i * i + i) / 2) % htsize;
        }
        
        if (i < htsize) {

            if (copy) { elements[idx] = d; }
            else { elements[idx] = std::move(d); }
            states[idx] = state::taken;
            ++size;
            
            if (!Remove(d, ++i)) { return true; }
            else { return false; }
        
        } else { return false; }
    }
}