namespace lasd {
    
    template <typename Data>
    StackVec<Data>::StackVec(const TraversableContainer<Data>& cntr)
        : Vector<Data>::Vector(cntr), head(cntr.Size()) {
        
        if (size < defaultSize) { Resize(defaultSize); }
    }


    template <typename Data>
    StackVec<Data>::StackVec(MappableContainer<Data>&& cntr) noexcept
        : Vector<Data>::Vector(std::move(cntr)), head(cntr.Size()) {
        
        if (size < defaultSize) { Resize(defaultSize); }
    }



    template<typename Data>
    StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& stk) {
        
        Vector<Data>::operator=(stk);
        head = stk.head;
        return *this;
    }
    

    template <typename Data>
    StackVec<Data>& StackVec<Data>:: operator=(StackVec<Data>&& stk) noexcept {
        
        Vector<Data>::operator=(std::move(stk));
        std::swap(head, stk.head);
        return *this;
    }
    


    template<typename Data>
    bool StackVec<Data>::operator==(const StackVec<Data>& stk) const noexcept {
    
        if (head == stk.head) {
            
            for (ulong i = 0; i < head; i++) { if (elements[i] != stk.elements[i]) return false; }
            
            return true;
        
        } else { return false; }
    }




    template<typename Data>
    const Data& StackVec<Data>::Top() const {
        
        if (head != 0) { return elements[head - 1]; }
        
        else { throw std::length_error("access to an empty stack."); }
    }


    template<typename Data>
    inline Data& StackVec<Data>::Top() {
        
        if (head != 0) { return elements[head - 1]; }
        
        else { throw std::length_error("access to an empty stack."); }
    }
    

    template<typename Data>
    inline void StackVec<Data>::Pop() {
        
        if (head != 0) { if (--head < size / 4) { Resize(size / 2); } }
        
        else { throw std::length_error("access to an empty stack."); }
    }


    template<typename Data>
    Data StackVec<Data>::TopNPop() {
        
        Data topEl { Top() };
        Pop();
        return topEl;
    }


    template<typename Data>
    void StackVec<Data>:: Push(const Data& d) {
        
        if (head == size) { Resize(size * 2); }

        elements[head++] = d;
    }


    template<typename Data>
    void StackVec<Data>::Push(Data&& d) {
        
        if (head == size) { Resize(size * 2); }

        elements[head++] = std::move(d);
    }
}