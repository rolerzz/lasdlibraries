namespace lasd {

//_________________________________________________________________________
//_________________________________________________________________________LinearContainer

    template <typename Data>
    bool LinearContainer<Data>::operator==(const LinearContainer<Data>& cntr) const noexcept {

        if (size == cntr.size) {
            
            for (ulong i = 0; i < size; i++) { if (operator[](i) != cntr.operator[](i)) return false; }
            return true;

        } else { return false; }
    }




    template <typename Data>
    const Data& LinearContainer<Data>::Front() const {

        if (size != 0) { return operator[](0); }
        
        else { throw std::length_error("trying acess to an empty container."); }
    }


    template <typename Data>
    Data& LinearContainer<Data>::Front() {

        if (size != 0) { return operator[](0); }
        
        else { throw std::length_error("trying acess to an empty container."); }
    }


    template <typename Data>
    const Data& LinearContainer<Data>::Back() const {

        if (size != 0) { return operator[](size - 1); }
        
        else { throw std::length_error("trying acess to an empty container."); }
    }


    template <typename Data>
    Data& LinearContainer<Data>::Back() {

        if (size != 0) { return operator[](size - 1); }
        
        else { throw std::length_error("trying acess to an empty container."); }
    }




    template <typename Data>
    inline void LinearContainer<Data>::Traverse(TraverseFun fun) const { PreOrderTraverse(fun); }


    template <typename Data>
    inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const {
        
        for (ulong i = 0; i < size; i++) { fun(operator[](i)); }
    }


    template <typename Data>
    inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const {

        for (ulong i = size; i > 0; i--) { fun(operator[](i - 1)); }
    }




    template <typename Data>
    inline void LinearContainer<Data>::Map(MapFun fun) { PreOrderMap(fun); }


    template <typename Data>
    inline void LinearContainer<Data>::PreOrderMap(MapFun fun) {
        
        for (ulong i = 0; i < size; i++) { fun(operator[](i)); }
    }


    template <typename Data>
    inline void LinearContainer<Data>::PostOrderMap(MapFun fun) {

        for (ulong i = size; i > 0; i--) { fun(operator[](i - 1)); }
    }





//_________________________________________________________________________
//_________________________________________________________________________SortableLinearContainer

    template <typename Data>
    void SortableLinearContainer<Data>::Sort() noexcept { QuickSort(0, size - 1); }


    template <typename Data>
    void SortableLinearContainer<Data>::QuickSort(ulong p, ulong r) noexcept {
        
        if (p < r) {

            ulong q = Partition(p, r);
            QuickSort(p, q);
            QuickSort(q + 1, r);
        }
    }


    template <typename Data>
    ulong SortableLinearContainer<Data>::Partition(ulong p, ulong r) noexcept {

        Data x = operator[](p);
        ulong i = p - 1;
        ulong j = r + 1;
        
        do {
            
            do { j--; } while (x < operator[](j));
            do { i++; } while (x > operator[](i));
            if (i < j) std::swap(operator[](i), operator[](j));

        } while (i < j);
        
        return j;
    }
}