#ifndef BST_HPP
#define BST_HPP

#include "../binarytree/lnk/binarytreelnk.hpp"

namespace lasd {

    template <typename Data>
    class BST:
        virtual public ClearableContainer,
        virtual public DictionaryContainer<Data>,
        virtual public BinaryTree<Data>,
        virtual BinaryTreeLnk<Data> {

        protected:

            using typename BinaryTreeLnk<Data>::NodeLnk;
            using BinaryTreeLnk<Data>::root;
            using Container::size;

        public:
            
            BST() = default;
            BST(const BST& bst) { operator=(bst); }
            BST(BST&& bst) noexcept { operator=(std::move(bst)); }
            
            BST(const TraversableContainer<Data>&) noexcept;
            BST(MappableContainer<Data>&&) noexcept;
            
            virtual ~BST() = default;
            
            BST& operator=(const BST&) noexcept;
            BST& operator=(BST&&) noexcept;
            
            bool operator==(const BST<Data>&) const noexcept;
            inline bool operator!=(const BST<Data>& bst) const noexcept { return !(operator==(bst)); }
            

            const Data& Min() const;
            Data MinNRemove();
            void RemoveMin();

            const Data& Max() const;
            Data MaxNRemove();
            void RemoveMax();

            const Data& Predecessor(const Data&) const;
            Data PredecessorNRemove(const Data&);
            void RemovePredecessor(const Data&);

            const Data& Successor(const Data&) const;
            Data SuccessorNRemove(const Data&);
            void RemoveSuccessor(const Data&);


            using BinaryTreeLnk<Data>::Clear;
            bool Exists(const Data&) const noexcept override;

            bool Insert(const Data&) noexcept override;
            bool Insert(Data&&) noexcept override;
            bool Remove(const Data&) noexcept override;
      
            using BinaryTreeLnk<Data>::Root;

        protected:

            Data DataNDelete(NodeLnk*);

            NodeLnk* Detach(NodeLnk*&) noexcept;

            NodeLnk* DetachMin(NodeLnk*&) noexcept;
            NodeLnk* DetachMax(NodeLnk*&) noexcept;

            NodeLnk* Skip2Left(NodeLnk*&) noexcept;
            NodeLnk* Skip2Right(NodeLnk*&) noexcept;

            const NodeLnk* const& FindPointerToMin(const NodeLnk* const&) const noexcept;
            NodeLnk*& FindPointerToMin(NodeLnk*&) noexcept;
            
            const NodeLnk* const& FindPointerToMax(const NodeLnk* const&) const noexcept;
            NodeLnk*& FindPointerToMax(NodeLnk*&) noexcept;
            
            const NodeLnk* const& FindPointerTo(const NodeLnk* const&, const Data&) const noexcept;
            NodeLnk*& FindPointerTo(NodeLnk*&, const Data&) noexcept;

            const NodeLnk* const* FindPointerToPredecessor(const NodeLnk* const&, const Data&) const noexcept;
            NodeLnk** FindPointerToPredecessor(NodeLnk*&, const Data&) noexcept;
            
            const NodeLnk* const* FindPointerToSuccessor(const NodeLnk* const&, const Data&) const noexcept;
            NodeLnk** FindPointerToSuccessor(NodeLnk*&, const Data&) noexcept;
    };
}

#include "bst.cpp"
#endif