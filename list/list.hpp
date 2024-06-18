#ifndef LIST_HPP
#define LIST_HPP
#include "../container/linear.hpp"
#include "../container/dictionary.hpp"

namespace lasd {

    template <typename Data>
    class List : 
        virtual public ClearableContainer,
        virtual public LinearContainer<Data>,
        virtual public DictionaryContainer<Data> {

        protected:

            using Container::size;

            struct Node {

                Data element;
                Node* next = nullptr;

                Node() = default;

                Node(const Data& d) : element(d) {}
                Node(Data&& d) noexcept { std::swap(element, d); }

                Node(const Node& nd) : element(nd.element) {}

                Node(Node&& nd) noexcept {
        
                    std::swap(element, nd.element);
                    std::swap(next, nd.next);
                }
                
                virtual ~Node() { delete next; }

                bool operator==(const Node& nd) const noexcept { return element == nd.element; }
                inline bool operator!=(const Node& nd) const noexcept { return !(operator==(nd)); }
            };

            Node* head = nullptr;
            Node* tail = nullptr;

        public:

            List() = default;
            
            List(const List& lst);
            List(List&& lst) noexcept { operator=(std::move(lst)); }
            
            List(const TraversableContainer<Data>&);
            List(MappableContainer<Data>&&);

            virtual ~List() { delete head; }

            List& operator=(const List&);
            List& operator=(List&&) noexcept;

            bool operator==(const List&) const noexcept;
            inline bool operator!=(const List& lst) const noexcept { return !(operator==(lst)); }
            
            const Data& operator[](const ulong) const override;
            Data& operator[](const ulong) override;


            void InsertAtFront(const Data&); 
            void InsertAtFront(Data&&); 
            void RemoveFromFront(); 
            Data FrontNRemove();

            void InsertAtBack(const Data&);
            void InsertAtBack(Data&&);

            void Clear() override;

            bool Insert(const Data&) override;
            bool Insert(Data&&) override;
            bool Remove(const Data&) override;


            using typename TraversableContainer<Data>::TraverseFun;
            void Traverse(TraverseFun) const override;

            void PreOrderTraverse(TraverseFun) const override;
            inline void PostOrderTraverse(TraverseFun fun) const override { PostOrderTraverse(fun, head); }


            using typename MappableContainer<Data>::MapFun;
            void Map(MapFun) override;

            void PreOrderMap(MapFun) override;
            inline void PostOrderMap(MapFun fun) { PostOrderMap(fun, head); }

        protected:

            void PostOrderTraverse(TraverseFun, const Node*) const;
            void PostOrderMap(MapFun, Node*);
    };
}

#include "list.cpp"
#endif