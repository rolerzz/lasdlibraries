namespace lasd {

//_________________________________________________________________________
//_________________________________________________________________________Node

    template<typename Data>
    bool BinaryTree<Data>::Node::operator==(const Node& nd) const noexcept {

        if (
            
            (Element() != nd.Element()) ||
            (HasLeftChild() != nd.HasLeftChild()) || (HasRightChild() != nd.HasRightChild())
        
        ) { return false; }
        
        return true;
    }


    template <typename Data>
    bool BinaryTree<Data>::Node::HasLeftChild() const noexcept {

        try { LeftChild(); return true; } catch (...) { return false; }
    }


    template <typename Data>
    bool BinaryTree<Data>::Node::HasRightChild() const noexcept {

        try { RightChild(); return true; } catch (...) { return false; }
    }





//_________________________________________________________________________
//_________________________________________________________________________BinaryTree

    template <typename Data>
    inline bool BinaryTree<Data>::operator==(const BinaryTree<Data>& bt) const noexcept {

        if (size != bt.Size()) { return false; }
        
        if (size != 0) { return CompareTrees(Root(), bt.Root()); }
        
        else { return true; }
    }




    template <typename Data>
    inline void BinaryTree<Data>::Traverse(TraverseFun fun) const { if (size != 0) PreOrderTraverse(fun, Root()); }


    template <typename Data>
    inline void BinaryTree<Data>::PreOrderTraverse(TraverseFun fun) const { if (size != 0) PreOrderTraverse(fun, Root()); }

    
    template <typename Data>
    inline void BinaryTree<Data>::PostOrderTraverse(TraverseFun fun) const { if (size != 0) PostOrderTraverse(fun, Root()); }


    template <typename Data>
    inline void BinaryTree<Data>::InOrderTraverse(TraverseFun fun) const { if (size != 0) InOrderTraverse(fun, Root()); }


    template <typename Data>
    inline void BinaryTree<Data>::BreadthTraverse(TraverseFun fun) const { if (size != 0) BreadthTraverse(fun, Root()); }



    template <typename Data>
    void BinaryTree<Data>::PreOrderTraverse(TraverseFun fun, const Node& nd) const {

        fun(nd.Element());
        if (nd.HasLeftChild()) { PreOrderTraverse(fun, nd.LeftChild()); }
        if (nd.HasRightChild()) { PreOrderTraverse(fun, nd.RightChild()); }
    }


    template <typename Data>
    void BinaryTree<Data>::PostOrderTraverse(TraverseFun fun, const Node& nd) const {

        if (nd.HasLeftChild()) { PostOrderTraverse(fun, nd.LeftChild()); }
        if (nd.HasRightChild()) { PostOrderTraverse(fun, nd.RightChild()); }
        fun(nd.Element());
    }


    template <typename Data>
    void BinaryTree<Data>::InOrderTraverse(TraverseFun fun, const Node& nd) const {

        if (nd.HasLeftChild()) { InOrderTraverse(fun, nd.LeftChild()); }
        fun(nd.Element());
        if (nd.HasRightChild()) { InOrderTraverse(fun, nd.RightChild()); }
    }


    template <typename Data>
    void BinaryTree<Data>::BreadthTraverse(TraverseFun fun, const Node& nd) const {

        QueueLst<Node const*> que;
        que.Enqueue(&nd);

        while (!que.Empty()) {
            
            if (que.Head()->HasLeftChild()) { que.Enqueue(&que.Head()->LeftChild()); }
            if (que.Head()->HasRightChild()) { que.Enqueue(&que.Head()->RightChild()); }
            fun(que.HeadNDequeue()->Element());
        }
    }


    template <typename Data>
    bool BinaryTree<Data>::CompareTrees(const Node& nd, const Node& nd2) const noexcept {    
        
        if (nd.HasLeftChild() == nd2.HasLeftChild() && nd.HasRightChild() == nd2.HasRightChild()) {

            if (nd.Element() == nd2.Element()) {

                if (nd.HasLeftChild() && !CompareTrees(nd.LeftChild(), nd2.LeftChild())) { return false; }
                if (nd.HasRightChild() && !CompareTrees(nd.RightChild(), nd2.RightChild())) { return false; }
                return true;
            
            } else { return false; }

        } else { return false; }
    }






//_________________________________________________________________________
//_________________________________________________________________________MutableBinaryTree

    template <typename Data>
    void MutableBinaryTree<Data>::Map(MapFun fun) {
        
        TraverseFun tFun = [&fun](const Data& d) { fun(const_cast<Data&>(d)); };

        static_cast<const MutableBinaryTree<Data>*>(this)->Traverse(tFun);
    }


    template <typename Data>
    void MutableBinaryTree<Data>::PreOrderMap(MapFun fun) {
        
        TraverseFun tFun = [&fun](const Data& d) { fun(const_cast<Data&>(d)); };

        static_cast<const MutableBinaryTree<Data>*>(this)->PreOrderTraverse(tFun);
    }


    template <typename Data>
    void MutableBinaryTree<Data>::PostOrderMap(MapFun fun) {
        
        TraverseFun tFun = [&fun](const Data& d) { fun(const_cast<Data&>(d)); };

        static_cast<const MutableBinaryTree<Data>*>(this)->PostOrderTraverse(tFun); 
    }


    template <typename Data>
    void MutableBinaryTree<Data>::InOrderMap(MapFun fun) {
        
        TraverseFun tFun = [&fun](const Data& d) { fun(const_cast<Data&>(d)); };

        static_cast<const MutableBinaryTree<Data>*>(this)->InOrderTraverse(tFun);
    }


    template <typename Data>
    void MutableBinaryTree<Data>::BreadthMap(MapFun fun) {
        
        TraverseFun tFun = [&fun](const Data& d) { fun(const_cast<Data&>(d)); };

        static_cast<const MutableBinaryTree<Data>*>(this)->BreadthTraverse(tFun);
    }





//_________________________________________________________________________
//_________________________________________________________________________BTPreOrderIterator

    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt) {

        if (bt.Size() != 0) {

            stk = StackVec<Node const*>();
            root = &bt.Root();
            cur = &bt.Root();
        }
    }


    template <typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& bt) {

        stk = StackVec<Node const*>(bt.stk);
        root = bt.root;
        cur = bt.cur;
        
        return *this;
    }


    template <typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& bt) noexcept {

        std::swap(stk, bt.stk);
        std::swap(root, bt.root);
        std::swap(cur, bt.cur);
        
        return *this;
    }


    template <typename Data>
    const Data& BTPreOrderIterator<Data>::operator*() const {
        
        if (cur != nullptr) { return cur->Element(); }
        
        else { throw std::out_of_range("The iterator is terminated."); }
    }



    template <typename Data>
    ForwardIterator<Data>& BTPreOrderIterator<Data>::operator++() {

        if (Terminated()) { throw std::out_of_range("The iterator is terminated."); }

        if(cur->HasRightChild()) { stk.Push(&(cur->RightChild())); }
        
        if(cur->HasLeftChild()) { stk.Push(&(cur->LeftChild())); }

        if(stk.Empty()) { cur = nullptr; }
        
        else { cur = stk.TopNPop(); }
        
        return *this;
    }



    template <typename Data>
    void BTPreOrderIterator<Data>::Reset() noexcept {

        stk.Clear();
        
        if (root != nullptr) { cur = root; }
    }





//_________________________________________________________________________
//_________________________________________________________________________BTPreOrderMutableIterator

    template <typename Data>
    BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(MutableBinaryTree<Data>& bt)
        : BTPreOrderIterator<Data>(bt) {}


    template <typename Data>
    BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(const BTPreOrderMutableIterator<Data>& bt) {

        return BTPreOrderIterator<Data>::operator=(bt);
    }


    template <typename Data>
    BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(BTPreOrderMutableIterator<Data>&& bt) noexcept {

        return BTPreOrderIterator<Data>::operator=(std::move(bt));
    }



    template <typename Data>
    Data& BTPreOrderMutableIterator<Data>::operator*() {
        
        if (cur != nullptr) { return const_cast<Data&>(cur->Element()); }
        
        else { throw std::out_of_range("The iterator is terminated."); }
    }






//_________________________________________________________________________
//_________________________________________________________________________BTPostOrderIterator

    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt) {

        if (bt.Size() != 0) {

            stk = StackVec<Node const*>();
            root = &bt.Root();
            stk.Push(root);
            Navigate2Left(root);
        }
    }


    template <typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& bt) {

        stk = StackVec<Node const*>(bt.stk);
        root = bt.root;
        cur = bt.cur;
        
        return *this;
    }


    template <typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& bt) noexcept {

        std::swap(stk, bt.stk);
        std::swap(root, bt.root);
        std::swap(cur, bt.cur);
        
        return *this;
    }


    template <typename Data>
    const Data& BTPostOrderIterator<Data>::operator*() const {

        if (cur != nullptr) { return cur->Element(); }
        
        else { throw std::out_of_range("the iterator is terminated."); }
    }



    template<typename Data>
    ForwardIterator<Data>& BTPostOrderIterator<Data>::operator++() {
        
        if (Terminated()) { throw std::out_of_range("the iterator is terminated."); }
        
        if (!(stk.Empty())) {

            if (stk.Top()->HasLeftChild() && cur == &(stk.Top()->LeftChild())) { cur = stk.TopNPop(); }
            
            else if (stk.Top()->HasRightChild() && cur == &(stk.Top()->RightChild())) { cur = stk.TopNPop(); }
            
            else { Navigate2Left(stk.Top()); }

        } else { cur = nullptr; }
        
        return *this;
    }



    template <typename Data>
    void BTPostOrderIterator<Data>::Reset() noexcept {

        stk.Clear();
        
        if (root != nullptr) { 
            
            stk.Push(root);
            Navigate2Left(root);
        }
    }



    template<typename Data>
    void BTPostOrderIterator<Data>::Navigate2Left(Node const* nd) {
        
        if ((nd->IsLeaf())) { cur = stk.TopNPop(); }
            
        if (nd->HasRightChild()) { stk.Push(&(nd->RightChild())); }
        
        if (nd->HasLeftChild()) {
            
            stk.Push(&(nd->LeftChild()));
            Navigate2Left(&(nd->LeftChild()));
        
        } else if (nd->HasRightChild()) { Navigate2Left(&(nd->RightChild())); }
    }





//_________________________________________________________________________
//_________________________________________________________________________BTPostOrderMutableIterator

    template <typename Data>
    BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(MutableBinaryTree<Data>& bt)
        : BTPostOrderIterator<Data>(bt) {}


    template <typename Data>
    BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(const BTPostOrderMutableIterator<Data>& bt) {

        return BTPostOrderIterator<Data>::operator=(bt);
    }


    template <typename Data>
    BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(BTPostOrderMutableIterator<Data>&& bt) noexcept {

        return BTPostOrderIterator<Data>::operator=(std::move(bt));
    }


    template <typename Data>
    Data& BTPostOrderMutableIterator<Data>::operator*() {
        
        if (cur != nullptr) { return const_cast<Data&>(cur->Element()); }
        
        else { throw std::out_of_range("The iterator is terminated."); }
    }





//_________________________________________________________________________
//_________________________________________________________________________BTInOrderIterator

    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt) {

        stk = StackVec<Node const*>();
        root = &(bt.Root());
        
        if (root == nullptr) { cur = nullptr; }
        
        else if (Navigate2Left(root) != nullptr) { cur = stk.TopNPop(); }
    }


    template <typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data>& bt) {

        stk = StackVec<Node const*>(bt.stk);
        root = bt.root;
        cur = bt.cur;
        
        return *this;
    }


    template <typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data>&& bt) noexcept {

        std::swap(stk, bt.stk);
        std::swap(root, bt.root);
        std::swap(cur, bt.cur);
        
        return *this;
    }


    template <typename Data>
    const Data& BTInOrderIterator<Data>::operator*() const {
        
        if (cur != nullptr) { return cur->Element(); }
        
        else { throw std::out_of_range("The iterator is terminated."); }
    }



    template <typename Data>
    ForwardIterator<Data>& BTInOrderIterator<Data>::operator++() {

        if (Terminated()) { throw std::out_of_range("The iterator is terminated."); }

        if (cur->HasRightChild()) { Navigate2Left(&(cur->RightChild())); }

        cur = (stk.Empty()) ? nullptr : stk.TopNPop();
        
        return *this;
    }



    template <typename Data>
    void BTInOrderIterator<Data>::Reset() noexcept { 
        
        stk.Clear();

        if (Navigate2Left(root) != nullptr) { cur = stk.TopNPop(); }
    }



    template<typename Data>
    BTInOrderIterator<Data>::Node const* BTInOrderIterator<Data>::Navigate2Left(Node const* nd) {
        
        while (nd != nullptr) {
            
            stk.Push(nd);
            nd = (nd->HasLeftChild()) ? &(nd->LeftChild()) : nullptr;
        }
        
        return (stk.Empty()) ? nullptr : stk.Top();
    }





//_________________________________________________________________________
//_________________________________________________________________________BTInOrderMutableIterator

    template <typename Data>
    BTInOrderMutableIterator<Data>::BTInOrderMutableIterator(MutableBinaryTree<Data>& bt)
        : BTInOrderIterator<Data>(bt) {}


    template <typename Data>
    BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(const BTInOrderMutableIterator<Data>& bt) {

        return BTInOrderIterator<Data>::operator=(bt);
    }


    template <typename Data>
    BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(BTInOrderMutableIterator<Data>&& bt) noexcept {

        return BTInOrderIterator<Data>::operator=(std::move(bt));
    }


    template <typename Data>
    Data& BTInOrderMutableIterator<Data>::operator*() {
        
        if (cur != nullptr) { return const_cast<Data&>(cur->Element()); }
        
        else { throw std::out_of_range("The iterator is terminated."); }
    }





//_________________________________________________________________________
//_________________________________________________________________________BTBreadthIterator

    template <typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt) {

        if (bt.Size() != 0) {

            que = QueueLst<Node const*>();
            root = &bt.Root();
            cur = &bt.Root();
        }
    }


    template <typename Data>
    BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data>& bt) {

        que = QueueLst<Node const*>(bt.que);
        root = bt.root;
        cur = bt.cur;
        
        return *this;
    }


    template <typename Data>
    BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data>&& bt) noexcept {

        std::swap(que, bt.que);
        std::swap(root, bt.root);
        std::swap(cur, bt.cur);
        
        return *this;
    }

    
    template <typename Data>
    const Data& BTBreadthIterator<Data>::operator*() const {
        
        if (cur != nullptr) { return cur->Element(); }
        
        else { throw std::out_of_range("The iterator is terminated."); }
    }



    template <typename Data>
    ForwardIterator<Data>& BTBreadthIterator<Data>::operator++() {

        if (Terminated()) { throw std::out_of_range("The iterator is terminated."); }

                   
        if (cur->HasLeftChild()) { que.Enqueue(&(cur->LeftChild())); }
        if (cur->HasRightChild()) { que.Enqueue(&(cur->RightChild())); }
        cur = (!que.Empty()) ? que.HeadNDequeue() : nullptr;
        
        return *this;
    }



    template <typename Data>
    void BTBreadthIterator<Data>::Reset() noexcept {

        que.Clear();
        
        if (root != nullptr) { cur = root; }
    }





//_________________________________________________________________________
//_________________________________________________________________________BTBreadthMutableIterator

    template <typename Data>
    BTBreadthMutableIterator<Data>::BTBreadthMutableIterator(MutableBinaryTree<Data>& bt)
        : BTBreadthIterator<Data>(bt) {}


    template <typename Data>
    BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(const BTBreadthMutableIterator<Data>& bt) {

        return BTBreadthIterator<Data>::operator=(bt);
    }


    template <typename Data>
    BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(BTBreadthMutableIterator<Data>&& bt) noexcept {

        return BTBreadthIterator<Data>::operator=(std::move(bt));
    }


    template <typename Data>
    Data& BTBreadthMutableIterator<Data>::operator*() {
        
        if (cur != nullptr) { return const_cast<Data&>(cur->Element()); }
        
        else { throw std::out_of_range("The iterator is terminated."); }
    }
}