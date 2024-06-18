#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

#include "../binarytree.hpp"

namespace lasd {

    template <typename Data>
    class BinaryTreeLnk : virtual public MutableBinaryTree<Data> {

        protected:

            using typename BinaryTree<Data>::Node;
            using typename MutableBinaryTree<Data>::MutableNode;
            using Container::size;

            struct NodeLnk : virtual MutableNode {
                
                NodeLnk* left = nullptr;
                NodeLnk* right = nullptr;
                Data element;
                
                NodeLnk(const Data& el) { element = el; }
                NodeLnk(Data&& el) { element = std::move(el); }
                
                virtual ~NodeLnk() { delete left; delete right; }

                const Data& Element() const override { return element; }
                Data& Element() noexcept override { return element; }

                const Node& RightChild() const override;      
                MutableNode& RightChild() override;

                const Node& LeftChild() const override;      
                MutableNode& LeftChild() override;
            };

            NodeLnk* root = nullptr;

        public:

            BinaryTreeLnk() = default;
            
            BinaryTreeLnk(const BinaryTreeLnk& bt) { operator=(bt); }
            BinaryTreeLnk(BinaryTreeLnk&& bt) noexcept { operator=(std::move(bt)); }
            
            BinaryTreeLnk(const TraversableContainer<Data>&);
            BinaryTreeLnk(MappableContainer<Data>&&) noexcept;

            virtual ~BinaryTreeLnk() { delete root; }

            BinaryTreeLnk& operator=(const BinaryTreeLnk&);
            BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept;


            const Node& Root() const override;
            MutableNode& Root() override;

            void Clear() override { delete root; root = nullptr; size = 0; }

        protected: NodeLnk* CopyTree(NodeLnk*);
    };
}

#include "binarytreelnk.cpp"
#endif