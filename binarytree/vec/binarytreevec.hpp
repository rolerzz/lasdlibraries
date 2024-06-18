#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

#include "../binarytree.hpp"

namespace lasd {

    template <typename Data>
    class BinaryTreeVec : virtual public MutableBinaryTree<Data> {

        protected:

            using typename BinaryTree<Data>::Node;
            using typename MutableBinaryTree<Data>::MutableNode;
            using Container::size;

            struct NodeVec : virtual MutableNode {

                BinaryTreeVec* tree = nullptr;
                ulong idx;
                Data element;
                
                NodeVec() = default;
                virtual ~NodeVec() = default;

                const Data& Element() const override { return element; }
                Data& Element() noexcept override { return element; }

                const Node& LeftChild() const override;
                MutableNode& LeftChild() override;

                const Node& RightChild() const override;
                MutableNode& RightChild() override;
            };

            NodeVec* elements = nullptr;
        
        public:

            BinaryTreeVec() = default;
            
            BinaryTreeVec(const BinaryTreeVec& bt) { operator=(bt); }
            BinaryTreeVec(BinaryTreeVec&& bt) noexcept { operator=(std::move(bt)); }
            
            BinaryTreeVec(const TraversableContainer<Data>&);
            BinaryTreeVec(MappableContainer<Data>&&) noexcept;
            
            virtual ~BinaryTreeVec() noexcept { delete[] elements; }

            BinaryTreeVec& operator=(const BinaryTreeVec&);
            BinaryTreeVec& operator=(BinaryTreeVec&&) noexcept;

            bool operator==(const BinaryTreeVec<Data>&) const noexcept;
            inline bool operator!=(const BinaryTreeVec<Data>& bt) const noexcept { return !(operator==(bt)); }

            
            const Node& Root() const override;
            MutableNode& Root() override;

            void Clear() override;

            using typename TraversableContainer<Data>::TraverseFun;
            void BreadthTraverse(TraverseFun) const override;

            using typename MappableContainer<Data>::MapFun;
            void BreadthMap(MapFun) override;
    };
}

#include "binarytreevec.cpp"
#endif