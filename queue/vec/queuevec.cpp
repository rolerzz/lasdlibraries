namespace lasd {

    template <typename Data>
    QueueVec<Data>::QueueVec(const TraversableContainer<Data>& cntr)
        : Vector<Data>::Vector(cntr), tail(cntr.Size()), numElem(cntr.Size()) {
        
        if (size < defaultSize) { Resize(defaultSize); }
    }


    template <typename Data>
    QueueVec<Data>::QueueVec(MappableContainer<Data>&& cntr) noexcept
        : Vector<Data>::Vector(std::move(cntr)), tail(cntr.Size()), numElem(cntr.Size()) {
    
        if (size < defaultSize) { Resize(defaultSize); }
    }



    template<typename Data>
    QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& que) {
        
        Vector<Data>::operator=(que);
        
        head = que.head;
        tail = que.tail;
        numElem = que.numElem;
        
        return *this;
    }
    

    template <typename Data>
    QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& que) noexcept {
        
        Vector<Data>::operator=(std::move(que));
        
        std::swap(head, que.head);
        std::swap(tail, que.tail);
        std::swap(numElem, que.numElem);
        
        return *this;
    }	  	
    


    template<typename Data>
    bool QueueVec<Data>::operator==(const QueueVec<Data>& que) const noexcept {
    
        if (numElem != que.numElem) { return false; }

        for (ulong i = 0; i < numElem; i++) {
            
            if (elements[(head + i) % size] != que.elements[(que.head + i) % que.size]) { return false; }
        }

        return true;
    }



    template <typename Data>
    const Data& QueueVec<Data>::Head() const {

        if (numElem != 0) { return elements[head]; }
        
        else { throw std::length_error("trying access to an empty queue."); }
    }


    template <typename Data>
    Data& QueueVec<Data>::Head() {

        if (numElem != 0) { return elements[head]; }
        
        else { throw std::length_error("trying access to an empty queue."); }
    }


    template <typename Data>
    void QueueVec<Data>::Dequeue() {

        if (numElem != 0) {
            
            ++head %= size;
            if (--numElem < size / 4) Resize(size / 2);
            
        } else { throw std::length_error("trying access to an empty queue."); }
    }


    template <typename Data>
    Data QueueVec<Data>::HeadNDequeue() {
        
        Data headEl = Head();
        Dequeue();
        return headEl;
    }


    template <typename Data>
    void QueueVec<Data>::Enqueue(const Data& d) {

        if (numElem ==  size) { Resize(size * 2); }

        elements[tail] = d;
        ++tail %= size;
        ++numElem;
    }


    template <typename Data>
    void QueueVec<Data>::Enqueue(Data&& d) {

        if (numElem == size) { Resize(size * 2); }

        elements[tail] = std::move(d);
        ++tail %= size;
        ++numElem;
    }



    
    template <typename Data>
    void QueueVec<Data>::Clear() {
        
        head = tail = numElem = 0;
        size = defaultSize;
        
        delete[] elements;
        elements = new Data[size];
    }


    template <typename Data>
    void QueueVec<Data>::Resize(ulong newSize) {

        if (newSize == size) { return; }

        ulong minSize = (newSize < defaultSize) ? defaultSize : newSize;
        Data* TmpEl = new Data[minSize];
        
        for (ulong i = head, j = 0; j < numElem; ++i %= size, ++j) { TmpEl[j] = elements[i]; }
        
        std::swap(elements, TmpEl);
        delete[] TmpEl;

        head = 0;
        tail = numElem;
        size = minSize;
    }
}