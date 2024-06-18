namespace lasd {

//_________________________________________________________________________
//_________________________________________________________________________NodeLnk

    template <typename Data>
    const BinaryTree<Data>::Node& BinaryTreeLnk<Data>::NodeLnk::RightChild() const { 
        
        if (right != nullptr) { return *right; }
        
        else { throw std::length_error("right child do not exists."); }
    }


    template <typename Data>
    MutableBinaryTree<Data>::MutableNode& BinaryTreeLnk<Data>::NodeLnk::RightChild() { 
        
        if (right != nullptr) { return *right; }
        
        else { throw std::length_error("right child do not exists."); }
    }


    template <typename Data>
    const BinaryTree<Data>::Node& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const { 
        
        if (left != nullptr) { return *left; }
        
        else { throw std::length_error("left child do not exists."); }
    }


    template <typename Data>
    MutableBinaryTree<Data>::MutableNode& BinaryTreeLnk<Data>::NodeLnk::LeftChild() { 
        
        if (left != nullptr) { return *left; }
        
        else { throw std::length_error("left child do not exists."); }
    }





//_________________________________________________________________________
//_________________________________________________________________________BinaryTreeLnk
    
    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data>& cntr) { 

        QueueLst<NodeLnk*> que;
        
        cntr.Traverse([&que, this](const Data& d) {
            
            if (que.Empty()) {
                
                root = new NodeLnk(d);
                que.Enqueue(root);
            
            } else if (que.Head()->IsLeaf()) {

                que.Head()->left = new NodeLnk(d);
                que.Enqueue(que.Head()->left);
            
            } else {
                
                que.Head()->right = new NodeLnk(d);
                que.Enqueue(que.Head()->right);
                que.Dequeue();
            }
        });

        size = cntr.Size();
    }


    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(MappableContainer<Data>&& cntr) noexcept {

        QueueLst<NodeLnk*> que;
        
        cntr.Map([&que, this](Data& d) {
            
            if (que.Empty()) {
                
                root = new NodeLnk(std::move(d));
                que.Enqueue(root);
            
            } else if (que.Head()->IsLeaf()) {

                que.Head()->left = new NodeLnk(std::move(d));
                que.Enqueue(que.Head()->left);
            
            } else {
                
                que.Head()->right = new NodeLnk(std::move(d));
                que.Enqueue(que.Head()->right);
                que.Dequeue();
            }
        });

        size = cntr.Size();
    }

    
    template <typename Data>
    BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& bt) {

        delete root;

        size = bt.size;
        root = CopyTree(bt.root);
        
        return *this;
    }
    
    
    template <typename Data>
    BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& bt) noexcept {

        std::swap(root, bt.root);
        std::swap(size, bt.size);
        
        return *this;
    }



    template <typename Data>
    const BinaryTree<Data>::Node& BinaryTreeLnk<Data>::Root() const {

        if (size != 0) { return *root; }
        
        else { throw std::length_error("the tree is empty."); }
    }

    template <typename Data>
    MutableBinaryTree<Data>::MutableNode& BinaryTreeLnk<Data>::Root() {

        if (size != 0) { return *root; }
        
        else { throw std::length_error("the tree is empty."); }
    }



    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::CopyTree(NodeLnk* nd) {

        if (nd == nullptr) { return nullptr; }

        NodeLnk* ndL = new NodeLnk { nd->element };
        ndL->left = CopyTree(nd->left);
        ndL->right = CopyTree(nd->right);
        
        return ndL;
    }
}