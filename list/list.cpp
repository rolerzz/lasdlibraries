namespace lasd {

    template <typename Data>
    List<Data>::List(const List<Data>& lst) {

        Node* nd = lst.head;

        while (nd != nullptr) {

            InsertAtBack(nd->element);
            nd = nd->next;
        }
    }

 
    template <typename Data>
    List<Data>::List(const TraversableContainer<Data>& cntr) {
        
        cntr.Traverse([this](const Data& d) { InsertAtBack(d); });
    }


    template <typename Data>
    List<Data>::List(MappableContainer<Data>&& cntr) {
        
        cntr.Map([this](Data& d) { InsertAtBack(std::move(d)); });
    }


    template <typename Data>
    List<Data>& List<Data>::operator=(const List<Data>& lst) {
        
        List<Data>* tmp = new List<Data>(lst);
        std::swap(*tmp, *this);
        delete tmp;

        return *this;
    }


    template <typename Data>
    List<Data>& List<Data>::operator=(List<Data>&& lst) noexcept {
        
        std::swap(size, lst.size);
        std::swap(head, lst.head);
        std::swap(tail, lst.tail);
        
        return *this;
    }


    template <typename Data>
    bool List<Data>::operator==(const List<Data>& lst) const noexcept {
        
        if (size != lst.size) { return false; }
        
        Node* nd = head; 
        Node* nd2 = lst.head;
        
        while (nd) {

            if (nd->element != nd2->element) { return false; }
            nd = nd->next;
            nd2 = nd2->next;
        }

        return true;
    }


    template <typename Data>
    const Data& List<Data>::operator[](const ulong idx) const {

        if (idx < size) {
            
            Node* nd = head;
            for (ulong i = 0; i < idx; i++) { nd = nd->next; }
            return nd->element;
        
        } else { throw std::out_of_range("index is out of bounds."); }
    }


    template <typename Data>
    Data& List<Data>::operator[](const ulong idx) {
        
        if (idx < size) {
            
            Node* nd = head;
            for (ulong i = 0; i < idx; i++ ) { nd = nd->next; }
            return nd->element;

        } else { throw std::out_of_range("index is out of bounds."); }
    }




    template <typename Data>
    void List<Data>::InsertAtFront(const Data& d) {

        Node* nd = new Node(d);
        nd->next = head;
        head = nd;
        
        if (tail == nullptr) { tail = head; }
        
        size++;
    }


    template <typename Data>
    void List<Data>::InsertAtFront(Data&& d) {

        Node* nd = new Node(std::move(d));
        nd->next = head;
        head = nd;
        
        if (tail == nullptr) { tail = head; }
        
        size++;
    }


    template <typename Data>
    void List<Data>::RemoveFromFront() {
        
        if (head != nullptr) {
            
            Node* nd = head;
            
            if (tail == head) { head = tail = nullptr; }
            else { head = head->next; }
            
            size--;
            nd->next = nullptr;
            delete nd;
        
        } else { throw std::length_error("trying access to an empty list."); }
    }


    template <typename Data>
    Data List<Data>::FrontNRemove() {

        if (head != nullptr) {
            
            Node* nd = head;
            
            if (tail == head) { head = tail = nullptr; }
            else { head = head->next; }
            
            size--;
            nd->next = nullptr;
            Data d(std::move(nd->element));
            delete nd;
            return d;

        } else { throw std::length_error("trying access to an empty list."); }
    }


    template <typename Data>
    void List<Data>::InsertAtBack(const Data& d) {
        
        Node* nd = new Node(d);
        
        if (tail == nullptr) { 
            
            tail = nd;
            head = tail;
        
        } else { 
            
            tail->next = nd;
            tail = tail->next;
        }

        size++;
    }


    template <typename Data>
    void List<Data>::InsertAtBack(Data&& d) {
        
        Node* nd = new Node(std::move(d));
        
        if (tail == nullptr) { 
            
            tail = nd;
            head = tail;
        
        } else { 
            
            tail->next = nd;
            tail = tail->next;
        }
        
        size++;
    }



    template <typename Data>
    void List<Data>::Clear() {

        delete head;
        head = tail = nullptr;
        size = 0;
    }



    template <typename Data>
    bool List<Data>::Insert(const Data& d) {

        for (Node* nd = head; nd != nullptr; nd = nd->next) { if (nd->element == d) return false; }

        InsertAtBack(d);
        return true;
    }


    template <typename Data>
    bool List<Data>::Insert(Data&& d) {
        
        for (Node* nd = head; nd != nullptr; nd = nd->next) { if (nd->element == d) return false; }

        InsertAtBack(std::move(d));
        return true; 
    }


    template <typename Data>
    bool List<Data>::Remove(const Data& d) {

        Node* lst = nullptr;
        
        for (Node** nd = &head; *nd != nullptr; lst = *nd, nd = &((*nd)->next)) {
            
            if ((*nd)->element == d) {
                
                Node* nd2 = *nd;
                *nd = nd2->next;
                nd2->next = nullptr;
                
                delete nd2;
                
                size--;
                
                if (tail == nd2) { tail = lst; }
                
                return true;
            }
        }
        
        return false;
    }




    template <typename Data>
    void List<Data>::Traverse(TraverseFun fun) const {
        
        for (Node* nd = head; nd != nullptr; nd = nd->next) { fun(nd->element); }
    }

    template <typename Data>
    void List<Data>::PreOrderTraverse(TraverseFun fun) const {
        
        for (Node* nd = head; nd != nullptr; nd = nd->next) { fun(nd->element); }
    }
    

    template <typename Data>
    void List<Data>::Map(MapFun fun) {
        
        for (Node* nd = head; nd != nullptr; nd = nd->next) { fun(nd->element); }
    }

    template <typename Data>
    void List<Data>::PreOrderMap(MapFun fun) {
        
        for (Node* nd = head; nd != nullptr; nd = nd->next) { fun(nd->element); }
    }
    



    template<typename Data>
    void List<Data>::PostOrderTraverse(TraverseFun fun, const Node* nd) const {

        if (nd != nullptr) {
            
            PostOrderTraverse(fun, nd->next);
            fun(nd->element);
        }
    }


    template<typename Data>
    void List<Data>::PostOrderMap(MapFun fun, Node* nd) {

        if (nd != nullptr) {
            
            PostOrderMap(fun, nd->next);
            fun(nd->element);
        }
    }
}