namespace lasd {

    template<typename Data>
    inline QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& que) {
        
        List<Data>::operator=(que);
        return *this;
    }

    template<typename Data>
    inline QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& que) noexcept {
        
        List<Data>::operator=(std::move(que));
        return *this;
    }
}