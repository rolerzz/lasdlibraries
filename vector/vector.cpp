namespace lasd {

//_________________________________________________________________________
//_________________________________________________________________________Vector

    template <typename Data>
    Vector<Data>::Vector(const ulong newSize) {
        
        size = newSize;
        elements = new Data[size];
    }



    template <typename Data>
    Vector<Data>::Vector(const Vector<Data>& vec) {
        
        size = vec.size;
        elements = new Data[size];
        std::copy(vec.elements, vec.elements + size, elements);
    }



    template <typename Data>
    Vector<Data>::Vector(const TraversableContainer<Data>& cntr) : Vector(cntr.Size()) {
        
        ulong i = 0;
        cntr.Traverse([this, &i](const Data& d) { elements[i++] = d; });
    }


    template <typename Data>
    Vector<Data>::Vector(MappableContainer<Data>&& cntr) : Vector(cntr.Size()) {
        
        ulong i = 0;
        cntr.Map([this, &i](Data& d) { elements[i++] = std::move(d); });
    }



    template <typename Data>
    Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vec) {
        
        Vector<Data>* tmp = new Vector<Data>(vec);
        std::swap(*tmp, *this);
        delete tmp;
        return *this;
    }


    template <typename Data>
    Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vec) noexcept {
        
        std::swap(size, vec.size);
        std::swap(elements, vec.elements);
        return *this;
    }



    template <typename Data>
    const Data& Vector<Data>::operator[](const ulong i) const {

        if (i < size) { return elements[i]; }
        
        else { throw std::out_of_range("index is out of bounds."); }
    }


    template <typename Data>
    Data& Vector<Data>::operator[](const ulong i) {

        if (i < size) { return elements[i]; }
        
        else { throw std::out_of_range("index is out of bounds."); }
    }




    template <typename Data>
    void Vector<Data>::Clear() {
        
        delete[] elements;
        elements = nullptr;
        size = 0;
    }


    template <typename Data>
    void Vector<Data>::Resize(const ulong newSize) {

        if (newSize == 0) { Clear(); }

        if (size != newSize) {
            
            Data* tmpEl = new Data[newSize];
            ulong minSize = std::min(size, newSize);
            
            for (ulong i = 0; i < minSize; i++) { std::swap(elements[i], tmpEl[i]); }
            
            size = newSize;
            std::swap(elements, tmpEl);
            delete[] tmpEl;
        }
    }





//_________________________________________________________________________
//_________________________________________________________________________SortableVector

    template <typename Data>
    SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector<Data>& vec) {
        
        Vector<Data>::operator=(vec);
        return *this;
    }

    template <typename Data>
    SortableVector<Data>& SortableVector<Data>::operator=(SortableVector<Data>&& vec) noexcept {
        
        Vector<Data>::operator=(std::move(vec));
        return *this;
    }
}