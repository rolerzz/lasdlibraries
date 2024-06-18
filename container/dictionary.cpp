namespace lasd {

    template <typename Data>
    inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& cntr) {

        bool allInserted = true;
        cntr.Traverse([this, &allInserted](const Data& d) { allInserted &= Insert(d); });
        return allInserted;
    }


    template <typename Data>
    inline bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& cntr) {

        bool allInserted = true;
        cntr.Map([this, &allInserted](Data& d) { allInserted &= Insert(std::move(d)); });
        return allInserted;
    }


    template <typename Data>
    inline bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& cntr) {

        bool allRemoved = true;
        cntr.Traverse([this, &allRemoved](const Data& d) { allRemoved &= Remove(d); });
        return allRemoved;
    }




    template <typename Data>
    inline bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& cntr) {

        bool someInserted = false;
        cntr.Traverse([this, &someInserted](const Data& d) { someInserted |= Insert(d); });
        return someInserted;
    }


    template <typename Data>
    inline bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& cntr) {

        bool someInserted = false;
        cntr.Map([this, &someInserted](Data& d) { someInserted |= Insert(std::move(d)); });
        return someInserted;
    }


    template <typename Data>
    inline bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& cntr) {

        bool someRemoved = false;
        cntr.Traverse([this, &someRemoved](const Data& d) { someRemoved |= Remove(d); });
        return someRemoved;
    }
}