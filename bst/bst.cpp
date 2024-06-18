namespace lasd {

//_________________________________________________________________________
//_________________________________________________________________________cnstrs & oprts

    template <typename Data>
    BST<Data>::BST(const TraversableContainer<Data>& cntr) noexcept {
        
        cntr.Traverse([this](const Data& d) { Insert(d); });
    }
    

    template <typename Data> BST<Data>::BST(MappableContainer<Data>&& cntr) noexcept {
        
        cntr.Map([this](Data& d) { Insert(std::move(d)); });
    }


    template<typename Data>
    BST<Data>& BST<Data>::operator=(const BST<Data>& bst) noexcept {
        
        BinaryTreeLnk<Data>::operator=(bst);
        return *this;
    } 


    template<typename Data>
    BST<Data>& BST<Data>::operator=(BST<Data>&& bst) noexcept {
        
        BinaryTreeLnk<Data>::operator=(std::move(bst));
        return *this;
    }


    template <typename Data>
    bool BST<Data>::operator==(const BST<Data>& bst) const noexcept { 
        
        if(size != bst.Size()) { return false; }
        
        if(size == 0) { return true; }

        BTInOrderIterator<Data> bt(*this);
        BTInOrderIterator<Data> bt2(bst);

        while(!bt.Terminated() && !bt2.Terminated()) {
            
            if(*bt != *bt2) { return false; }
            
            ++bt;
            ++bt2;
        }

        return bt.Terminated() && bt2.Terminated();
    }





//_________________________________________________________________________
//_________________________________________________________________________public funs

    template<typename Data>
    const Data& BST<Data>::Min() const {
        
        if (size != 0) { return FindPointerToMin(root)->element; }

        else { throw std::length_error("the bst is empty."); }
    }


    template<typename Data>
    Data BST<Data>::MinNRemove() {

        Data d = Min();
        RemoveMin();
        return d;
    }


    template<typename Data>
    void BST<Data>::RemoveMin() {

        if (size != 0) { delete DetachMin(root); }
        
        else { throw std::length_error("the bst is empty."); }
    }



    template<typename Data>
    const Data& BST<Data>::Max() const {

        if (size != 0) { return FindPointerToMax(root)->element; }

        else { throw std::length_error("the bst is empty."); }
    }


    template<typename Data>
    Data BST<Data>::MaxNRemove() {

        Data d = Max();
        RemoveMax();
        return d;
    }


    template<typename Data>
    void BST<Data>::RemoveMax() {
        
        if (root != nullptr) { delete DetachMax(root); }
        
        else { throw std::length_error("the bst is empty."); }
    }




    template<typename Data>
    const Data& BST<Data>::Predecessor(const Data& d) const {

        NodeLnk* const* nd = const_cast<NodeLnk**>(FindPointerToPredecessor(root, d));
    
        if(nd != nullptr) { return (*nd)->element; }
        
        else { throw std::length_error("predecessor not found."); }
    }


    template<typename Data>
    Data BST<Data>::PredecessorNRemove(const Data& d) {

        NodeLnk** nd = FindPointerToPredecessor(root, d);
        
        if(nd != nullptr) { return DataNDelete(Detach(*nd)); }
        
        else { throw std::length_error("predecessor not found."); }
    }


    template<typename Data>
    void BST<Data>::RemovePredecessor(const Data& d) {

        NodeLnk** nd = FindPointerToPredecessor(root, d);
        
        if (nd != nullptr) { delete Detach(*nd); }
        
        else { throw std::length_error("predecessor not found."); }
    }



    template<typename Data>
    const Data& BST<Data>::Successor(const Data& d) const {

        NodeLnk* const* nd = const_cast<NodeLnk**>(FindPointerToSuccessor(root, d));
    
        if (nd != nullptr) { return (*nd)->element; }
        
        else { throw std::length_error("successor not found."); }
    }


    template<typename Data>
    Data BST<Data>::SuccessorNRemove(const Data& d) {
        
        NodeLnk** nd = FindPointerToSuccessor(root, d);
        
        if (nd != nullptr) { return DataNDelete(Detach(*nd)); }
        
        else { throw std::length_error("successor not found."); }
    }


    template<typename Data>
    void BST<Data>::RemoveSuccessor(const Data& d) {

        NodeLnk** nd = FindPointerToSuccessor(root, d);
        
        if (nd != nullptr) { delete Detach(*nd); }
        
        else { throw std::length_error("successor not found."); }
    }




    template<typename Data>
    bool BST<Data>::Exists(const Data& d) const noexcept {

        return FindPointerTo(const_cast<NodeLnk*&>(root), d) != nullptr;
    }




    template <typename Data>
    bool BST<Data>::Insert(const Data& d) noexcept {
        
        NodeLnk*& nd = FindPointerTo(root, d);

        if (nd == nullptr) {
            
            nd = new NodeLnk(d);
            ++size;
            return true;    
        }

        return false;
    }
    

    template <typename Data>
    bool BST<Data>::Insert(Data&& d) noexcept {

        NodeLnk*& nd = FindPointerTo(root, d);

        if (nd == nullptr) {
            
            nd = new NodeLnk(std::move(d));
            ++size;
            return true;    
        }

        return false;
    }


    template<typename Data>
    bool BST<Data>::Remove(const Data& d) noexcept {

        NodeLnk*& ptr = FindPointerTo(root, d);
        
        if (ptr == nullptr) { return false; }
        
        delete Detach(ptr);
        return true;
    }





//_________________________________________________________________________
//_________________________________________________________________________protected funs

    template <typename Data>
    Data BST<Data>::DataNDelete(NodeLnk* nd) {

        Data d = std::move(nd->element);
        delete nd;
        return d;
    }




    template <typename Data>
    BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& nd) noexcept {

        if(nd != nullptr) {
            
            if(nd->left == nullptr) { return Skip2Right(nd); }
            
            else if(nd->right == nullptr) { return Skip2Left(nd); }
            
            else {

                NodeLnk* nd2 = DetachMax(nd->left);
                std::swap(nd->element, nd2->element);
                return nd2;
            }
        }

        return nullptr;
    }


    template <typename Data>
    BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& nd) noexcept { return Skip2Right(FindPointerToMin(nd)); }


    template <typename Data>
    BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk*& nd) noexcept { return Skip2Left(FindPointerToMax(nd)); }




    template <typename Data>
    BST<Data>::NodeLnk* BST<Data>::Skip2Left(NodeLnk*& nd) noexcept {

        NodeLnk* left = nullptr;

        if (nd != nullptr) {

            std::swap(left, nd->left);
            std::swap(left, nd);
            --size;
        }

        return left;
    }


    template <typename Data>
    BST<Data>::NodeLnk* BST<Data>::Skip2Right(NodeLnk*& nd) noexcept {

        NodeLnk* right = nullptr;

        if (nd != nullptr) {

            std::swap(right, nd->right);
            std::swap(right, nd);
            --size;
        }

        return right;
    }




    template <typename Data>
    const BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(const NodeLnk* const& nd) const noexcept {

        if (nd->left != nullptr) { return FindPointerToMin(nd->left); }
        
        else { return nd; }
    }


    template <typename Data>
    BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(NodeLnk*& nd) noexcept {

        return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(nd));
    }




    template <typename Data>
    const BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(const NodeLnk* const& nd) const noexcept {

        if (nd->right != nullptr) { return FindPointerToMax(nd->right); }
        
        else { return nd; }
    }


    template <typename Data>
    BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(NodeLnk*& nd) noexcept {

        return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMax(nd));
    }




    template <typename Data>
    const BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(const NodeLnk* const& nd, const Data& d) const noexcept {

        if (nd != nullptr) {
            
            if (d < nd->element) { return FindPointerTo(nd->left, d); }
            if (d > nd->element) { return FindPointerTo(nd->right, d); }
        }

        return nd;
    }


    template <typename Data>
    BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& nd, const Data& d) noexcept {

        return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerTo(nd, d));
    }




    template<typename Data>
    const BST<Data>::NodeLnk* const* BST<Data>::FindPointerToPredecessor(const NodeLnk* const& nd, const Data & d) const noexcept {
        
        const NodeLnk* const* ptr = &nd;
        const NodeLnk* const* prdc = nullptr;
        
        while (*ptr != nullptr && (*ptr)->element != d) {
            
            if ((*ptr)->element < d) {
                
                prdc = ptr;
                ptr = &((*ptr)->right);

            } else if ((*ptr)->element > d) { ptr = &((*ptr)->left); }
        }

        if (*ptr != nullptr && (*ptr)->HasLeftChild()) { return &FindPointerToMax((*ptr)->left); }
        
        return prdc;
    }


    template<typename Data>
    BST<Data>::NodeLnk** BST<Data>::FindPointerToPredecessor(NodeLnk*& nd, const Data& d) noexcept {
        
        return const_cast<NodeLnk**>(static_cast<const BST<Data>*>(this)->FindPointerToPredecessor(nd, d));
    }




    template<typename Data>
    const BST<Data>::NodeLnk* const* BST<Data>::FindPointerToSuccessor(const NodeLnk* const& nd, const Data& d) const noexcept {
        
        const NodeLnk* const* ptr = &nd;
        const NodeLnk* const* succ = nullptr;
        
        while (*ptr != nullptr && (*ptr)->element != d) {
            
            if ((*ptr)->element > d) {

                succ = ptr;
                ptr = &((*ptr)->left);

            } else if ((*ptr)->element < d) { ptr = &((*ptr)->right); }
        }

        if (*ptr != nullptr && (*ptr)->HasRightChild()) { return &FindPointerToMin((*ptr)->right); }

        return succ;
    }


    template<typename Data>
    BST<Data>::NodeLnk** BST<Data>::FindPointerToSuccessor(NodeLnk*& nd, const Data& d) noexcept {
        
        return const_cast<NodeLnk**>(static_cast<const BST<Data>*>(this)->FindPointerToSuccessor(nd,d));
    }
}