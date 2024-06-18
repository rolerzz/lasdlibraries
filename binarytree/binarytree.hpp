#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP
#include "../stack/vec/stackvec.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../iterator/iterator.hpp"

namespace lasd {

    template <typename Data>
    class BinaryTree :
        virtual public PreOrderTraversableContainer<Data>,
        virtual public PostOrderTraversableContainer<Data>,
        virtual public InOrderTraversableContainer<Data>,
        virtual public BreadthTraversableContainer<Data> {

        protected: using Container::size;

        public:

            struct Node {

                protected:

                    bool operator==(const Node&) const noexcept;
                    inline bool operator!=(const Node& nd) const noexcept { return !(operator==(nd)); }

                public:

                    friend class BinaryTree<Data>;

                    virtual ~Node() = default;

                    Node& operator=(const Node&) = delete;
                    Node& operator=(Node&&) noexcept = delete;

                    virtual const Data& Element() const = 0;
                    virtual const Node& LeftChild() const = 0;
                    virtual const Node& RightChild() const = 0;

                    bool HasLeftChild() const noexcept;
                    bool HasRightChild() const noexcept;
                    inline bool IsLeaf() const noexcept { return !HasLeftChild() && !HasRightChild(); }
            };


            virtual ~BinaryTree() = default;

            BinaryTree& operator=(const BinaryTree&) = delete;
            BinaryTree& operator=(BinaryTree&&) noexcept = delete;

            bool operator==(const BinaryTree&) const noexcept;
            inline bool operator!=(const BinaryTree& bt) const noexcept { return !(operator==(bt)); }


            virtual const Node& Root() const = 0;


            using typename TraversableContainer<Data>::TraverseFun;
            void Traverse(TraverseFun) const override;

            inline void PreOrderTraverse(TraverseFun) const override;
            inline void PostOrderTraverse(TraverseFun) const override;
            inline void InOrderTraverse(TraverseFun) const override;
            inline void BreadthTraverse(TraverseFun) const override;

        protected:

            void PreOrderTraverse(TraverseFun, const Node&) const;
            void PostOrderTraverse(TraverseFun, const Node&) const;
            void InOrderTraverse(TraverseFun, const Node&) const;
            void BreadthTraverse(TraverseFun, const Node&) const;
            bool CompareTrees(const Node&, const Node&) const noexcept;
    };





    template <typename Data>
    class MutableBinaryTree :
        virtual public BinaryTree<Data>,
        virtual public ClearableContainer,
        virtual public PreOrderMappableContainer<Data>,
        virtual public PostOrderMappableContainer<Data>,
        virtual public InOrderMappableContainer<Data>,
        virtual public BreadthMappableContainer<Data> {

        protected:

            using Container::size;
            using BinaryTree<Data>::Root;
            using typename BinaryTree<Data>::Node;

        public:

            struct MutableNode : virtual BinaryTree<Data>::Node {

                protected:

                    using BinaryTree<Data>::Node::Element;
                    using BinaryTree<Data>::Node::LeftChild;
                    using BinaryTree<Data>::Node::RightChild;

                public:

                    friend class MutableBinaryTree<Data>;

                    virtual ~MutableNode() = default;

                    MutableNode& operator=(const MutableNode&) = delete;
                    MutableNode& operator=(MutableNode&&) noexcept = delete;

                    virtual Data& Element() noexcept = 0;
                    virtual MutableNode& LeftChild() = 0;
                    virtual MutableNode& RightChild() = 0;
            };


            virtual ~MutableBinaryTree() = default;

            MutableBinaryTree& operator=(const MutableBinaryTree&) noexcept = delete;
            MutableBinaryTree& operator=(MutableBinaryTree&&) noexcept = delete;


            virtual MutableNode& Root() = 0;

            using typename TraversableContainer<Data>::TraverseFun;
            using typename MappableContainer<Data>::MapFun;
            void Map(MapFun) override;

            void PreOrderMap(MapFun) override;
            void PostOrderMap(MapFun) override;
            void InOrderMap(MapFun) override;
            void BreadthMap(MapFun) override;
    };





    template <typename Data>
    class BTPreOrderIterator :
        virtual public ForwardIterator<Data>,
        virtual public ResettableIterator<Data> {

        protected:
            
            using Node = typename BinaryTree<Data>::Node;
            StackVec<Node const*> stk;
            Node const* root = nullptr;
            Node const* cur = nullptr;

        public:

            BTPreOrderIterator(const BinaryTree<Data>&);
            BTPreOrderIterator(const BTPreOrderIterator& bt) { operator=(bt); }
            BTPreOrderIterator(BTPreOrderIterator&& bt) noexcept { operator=(std::move(bt)); }
            
            virtual ~BTPreOrderIterator() = default;

            BTPreOrderIterator& operator=(const BTPreOrderIterator&);
            BTPreOrderIterator& operator=(BTPreOrderIterator&&) noexcept;

            bool operator==(const BTPreOrderIterator& bt) const noexcept { return root == bt.root && cur == bt.cur; }
            inline bool operator!=(const BTPreOrderIterator& bt) const noexcept { return !(operator==(bt)); }

            const Data& operator*() const override;
            ForwardIterator<Data>& operator++() override;


            bool Terminated() const noexcept override { return cur == nullptr; }
            void Reset() noexcept override;
    };





    template <typename Data>
    class BTPreOrderMutableIterator :
        virtual public MutableIterator<Data>,
        virtual public BTPreOrderIterator<Data> {

        protected:

            using MutableNode = typename MutableBinaryTree<Data>::MutableNode;
            using BTPreOrderIterator<Data>::stk;
            using BTPreOrderIterator<Data>::root;
            using BTPreOrderIterator<Data>::cur;

        public:

            BTPreOrderMutableIterator(MutableBinaryTree<Data>&);
            BTPreOrderMutableIterator(const BTPreOrderMutableIterator& bt) : BTPreOrderIterator<Data>(bt) {}
            BTPreOrderMutableIterator(BTPreOrderMutableIterator&& bt) noexcept : BTPreOrderIterator<Data>(std::move(bt)) {}

            virtual ~BTPreOrderMutableIterator() = default;

            BTPreOrderMutableIterator& operator=(const BTPreOrderMutableIterator&);
            BTPreOrderMutableIterator& operator=(BTPreOrderMutableIterator&&) noexcept;

            using BTPreOrderIterator<Data>::operator==;
            using BTPreOrderIterator<Data>::operator!=;

            Data& operator*() override;
    };





    template <typename Data>
    class BTPostOrderIterator :
        virtual public ForwardIterator<Data>,
        virtual public ResettableIterator<Data> {

        protected:
            
            using Node = typename BinaryTree<Data>::Node;
            StackVec<Node const*> stk;
            Node const* root = nullptr;
            Node const* cur = nullptr;

        public:
            
            BTPostOrderIterator(const BinaryTree<Data>&);
            BTPostOrderIterator(const BTPostOrderIterator& bt) { operator=(bt); }
            BTPostOrderIterator(BTPostOrderIterator&& bt) noexcept { operator=(std::move(bt)); }
            
            virtual ~BTPostOrderIterator() = default;

            BTPostOrderIterator& operator=(const BTPostOrderIterator&);
            BTPostOrderIterator& operator=(BTPostOrderIterator&&) noexcept;

            bool operator==(const BTPostOrderIterator& bt) const noexcept { return root == bt.root && cur == bt.cur; }
            inline bool operator!=(const BTPostOrderIterator& bt) const noexcept { return !(operator==(bt)); }

            const Data& operator*() const override;
            ForwardIterator<Data>& operator++() override;


            bool Terminated() const noexcept override { return cur == nullptr; }
            void Reset() noexcept override;

        protected: void Navigate2Left(Node const*);
    };





    template <typename Data>
    class BTPostOrderMutableIterator :
        virtual public MutableIterator<Data>,
        virtual public BTPostOrderIterator<Data> {

        protected:

            using MutableNode = typename MutableBinaryTree<Data>::MutableNode;
            using BTPostOrderIterator<Data>::Navigate2Left;
            using BTPostOrderIterator<Data>::stk;
            using BTPostOrderIterator<Data>::root;
            using BTPostOrderIterator<Data>::cur;

        public:

            BTPostOrderMutableIterator(MutableBinaryTree<Data>&);
            BTPostOrderMutableIterator(const BTPostOrderMutableIterator& bt) : BTPostOrderIterator<Data>(bt) {}
            BTPostOrderMutableIterator(BTPostOrderMutableIterator&& bt) noexcept : BTPostOrderIterator<Data>(std::move(bt)) {}

            virtual ~BTPostOrderMutableIterator() = default;

            BTPostOrderMutableIterator& operator=(const BTPostOrderMutableIterator&);
            BTPostOrderMutableIterator& operator=(BTPostOrderMutableIterator&&) noexcept;

            using BTPostOrderIterator<Data>::operator==;
            using BTPostOrderIterator<Data>::operator!=;

            Data& operator*() override;
    };





    template <typename Data>
    class BTInOrderIterator :
        virtual public ForwardIterator<Data>,
        virtual public ResettableIterator<Data> {

        protected:
            
            using Node = typename BinaryTree<Data>::Node;
            StackVec<Node const*> stk;
            Node const* root = nullptr;
            Node const* cur = nullptr;

        public:

            BTInOrderIterator(const BinaryTree<Data>&);
            BTInOrderIterator(const BTInOrderIterator& bt) { operator=(bt); }
            BTInOrderIterator(BTInOrderIterator&& bt) noexcept { operator=(std::move(bt)); }
            
            virtual ~BTInOrderIterator() = default;

            BTInOrderIterator& operator=(const BTInOrderIterator&);
            BTInOrderIterator& operator=(BTInOrderIterator&&) noexcept;

            bool operator==(const BTInOrderIterator& bt) const noexcept { return root == bt.root && cur == bt.cur; }
            inline bool operator!=(const BTInOrderIterator& bt) const noexcept { return !(operator==(bt)); }

            const Data& operator*() const override;
            ForwardIterator<Data>& operator++() override;


            bool Terminated() const noexcept override { return cur == nullptr; }
            void Reset() noexcept override;
        
        protected: Node const* Navigate2Left(Node const*);
    };





    template <typename Data>
    class BTInOrderMutableIterator :
        virtual public MutableIterator<Data>,
        virtual public BTInOrderIterator<Data> {

        protected:

            using MutableNode = typename MutableBinaryTree<Data>::MutableNode;
            using BTInOrderIterator<Data>::Navigate2Left;
            using BTInOrderIterator<Data>::stk;
            using BTInOrderIterator<Data>::root;
            using BTInOrderIterator<Data>::cur;

        public:

            BTInOrderMutableIterator(MutableBinaryTree<Data>&);
            BTInOrderMutableIterator(const BTInOrderMutableIterator& bt) : BTInOrderIterator<Data>(bt) {}
            BTInOrderMutableIterator(BTInOrderMutableIterator&& bt) noexcept : BTInOrderIterator<Data>(std::move(bt)) {}

            virtual ~BTInOrderMutableIterator() = default;

            BTInOrderMutableIterator& operator=(const BTInOrderMutableIterator&);
            BTInOrderMutableIterator& operator=(BTInOrderMutableIterator&&) noexcept;

            using BTInOrderIterator<Data>::operator==;
            using BTInOrderIterator<Data>::operator!=;

            Data& operator*() override;
    };





    template <typename Data>
    class BTBreadthIterator :
        virtual public ForwardIterator<Data>,
        virtual public ResettableIterator<Data> {

        protected:
            
            using Node = typename BinaryTree<Data>::Node;
            QueueLst<Node const*> que;
            Node const* root = nullptr;
            Node const* cur = nullptr;

        public:

            BTBreadthIterator(const BinaryTree<Data>&);
            BTBreadthIterator(const BTBreadthIterator& bt) { operator=(bt); }
            BTBreadthIterator(BTBreadthIterator&& bt) noexcept { operator=(std::move(bt)); }

            virtual ~BTBreadthIterator() = default;

            BTBreadthIterator& operator=(const BTBreadthIterator&);
            BTBreadthIterator& operator=(BTBreadthIterator&&) noexcept;

            bool operator==(const BTBreadthIterator& bt) const noexcept { return root == bt.root && cur == bt.cur; }
            inline bool operator!=(const BTBreadthIterator& bt) const noexcept { return !(operator==(bt)); }

            const Data& operator*() const override;
            ForwardIterator<Data>& operator++() override;


            bool Terminated() const noexcept override { return cur == nullptr; }
            void Reset() noexcept override;
    };





    template <typename Data>
    class BTBreadthMutableIterator :
        virtual public MutableIterator<Data>,
        virtual public BTBreadthIterator<Data> {

    protected:

            using MutableNode = typename MutableBinaryTree<Data>::MutableNode;
            using BTBreadthIterator<Data>::que;
            using BTBreadthIterator<Data>::root;
            using BTBreadthIterator<Data>::cur;

        public:

            BTBreadthMutableIterator(MutableBinaryTree<Data>&);
            BTBreadthMutableIterator(const BTBreadthMutableIterator& bt) : BTBreadthIterator<Data>(bt) {}
            BTBreadthMutableIterator(BTBreadthMutableIterator&& bt) noexcept : BTBreadthIterator<Data>(std::move(bt)) {}

            virtual ~BTBreadthMutableIterator() = default;

            BTBreadthMutableIterator& operator=(const BTBreadthMutableIterator&);
            BTBreadthMutableIterator& operator=(BTBreadthMutableIterator&&) noexcept;

            using BTBreadthIterator<Data>::operator==;
            using BTBreadthIterator<Data>::operator!=;

            Data& operator*() override;
    };
}

#include "binarytree.cpp"
#endif