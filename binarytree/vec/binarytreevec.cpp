namespace lasd {

//_________________________________________________________________________
//_________________________________________________________________________NodeVec

    template <typename Data>
    const BinaryTree<Data>::Node& BinaryTreeVec<Data>::NodeVec::LeftChild() const { 
        
        ulong lIdx = 2 * idx + 1;
        
        if (lIdx < tree->size) { return tree->elements[lIdx]; }
        
        else { throw std::length_error("right child do not exists."); }
    }

    
    template <typename Data>
    MutableBinaryTree<Data>::MutableNode& BinaryTreeVec<Data>::NodeVec::LeftChild() { 
        
        ulong lIdx = 2 * idx + 1;
        
        if (lIdx < tree->size) { return tree->elements[lIdx]; }
        
        else { throw std::length_error("right child do not exists."); }
    }

    
    template <typename Data>
    const BinaryTree<Data>::Node& BinaryTreeVec<Data>::NodeVec::RightChild() const { 
        
        ulong rIdx = 2 * idx + 2;
        
        if (rIdx < tree->size) { return tree->elements[rIdx]; }
        
        else { throw std::length_error("right child do not exists."); }
    }


    template <typename Data>
    MutableBinaryTree<Data>::MutableNode& BinaryTreeVec<Data>::NodeVec::RightChild() { 
        
        ulong rIdx = 2 * idx + 2;
        
        if (rIdx < tree->size) { return tree->elements[rIdx]; }
        
        else { throw std::length_error("right child do not exists."); }
    }
    




//_________________________________________________________________________
//_________________________________________________________________________BinaryTreeVec

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data>& cntr) {
        
        size = 0;
        elements = new NodeVec[cntr.Size()];

        cntr.Traverse([this](const Data& d) { 

            elements[size].tree = this; 
            elements[size].idx = size; 
            elements[size].element = d;
            ++size; 
        });
    }


    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data>&& cntr) noexcept {
        
        size = 0;
        elements = new NodeVec[cntr.Size()];
        
        cntr.Map([this](Data& d) { 

            elements[size].tree = this; 
            elements[size].idx = size;
            elements[size].element = std::move(d);
            ++size; 
        });
    }


    template <typename Data>
    BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& bt) {
        
        delete[] elements;

        size = bt.Size();
        elements = new NodeVec[size];
        
        for (ulong i = 0; i < size; i++) {
            
            elements[i].element = bt.elements[i].element;
            elements[i].tree = this;
            elements[i].idx = bt.elements[i].idx;
        }

        return *this;
    }


    template <typename Data>
    BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& bt) noexcept {
        
        std::swap(elements, bt.elements);
        std::swap(size, bt.size);

        for (ulong i = 0; i < size; i++) { elements[i].tree = this; }

        return *this;
    }


    template <typename Data>
    bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& bt) const noexcept {
        
        if (size != bt.Size()) return false;
        
        for (ulong i = 0; i < size; i++) {
            
            if (elements[i].element != bt.elements[i].element) { return false; }
        }
        
        return true;
    }



    template<typename Data>
    const BinaryTree<Data>::Node& BinaryTreeVec<Data>::Root() const {
        
        if (size != 0) { return elements[0]; }
        
        else { throw std::length_error("the tree is empty."); }
    }


    template<typename Data>
    MutableBinaryTree<Data>::MutableNode& BinaryTreeVec<Data>::Root() {
        
        if (size != 0) { return elements[0]; }
        
        else { throw std::length_error("the tree is empty."); }
    }



    template <typename Data>
    void BinaryTreeVec<Data>::Clear() {
        
        delete[] elements;
        elements = nullptr;
        size = 0;
    }



    template<typename Data>
    void BinaryTreeVec<Data>::BreadthTraverse(TraverseFun fun) const {
        
        for (ulong i = 0; i < size; i++) { fun(elements[i].element); }
    }


    template<typename Data>
    void BinaryTreeVec<Data>::BreadthMap(MapFun fun) {
        
        for (ulong i = 0; i < size; i++) { fun(elements[i].element); }
    }
}