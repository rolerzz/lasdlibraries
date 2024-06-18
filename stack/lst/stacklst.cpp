namespace lasd {

    template <typename Data>
    inline StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& stk) {

        List<Data>::operator=(stk);
        return *this;
    }


    template <typename Data>
    inline StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& stk) noexcept {

        List<Data>::operator=(std::move(stk));
        return *this;
    }
}