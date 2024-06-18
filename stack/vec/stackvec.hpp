#ifndef STACKVEC_HPP
#define STACKVEC_HPP
#include "../stack.hpp"
#include "../../vector/vector.hpp"
#define defaultSize 12UL

namespace lasd {

    template <typename Data>
    class StackVec : 
        virtual public Stack<Data>, 
        virtual protected Vector<Data> {

        protected:
            
            ulong head = 0;
            using Vector<Data>::size;
            using Vector<Data>::elements;

        public:

            StackVec() : Vector<Data>(defaultSize) {}

            StackVec(const StackVec& stk) { operator=(stk); }
            StackVec(StackVec&& stk) noexcept { operator=(std::move(stk)); }

            StackVec(const TraversableContainer<Data>&);
            StackVec(MappableContainer<Data>&&) noexcept;

            virtual ~StackVec() = default;
        
            StackVec<Data>& operator=(const StackVec&);
            StackVec<Data>& operator=(StackVec&&) noexcept;

            inline bool operator==(const StackVec& stk) const noexcept;
            inline bool operator!=(const StackVec& stk) const noexcept { return !(operator==(stk)); }
            

            const Data& Top() const override;
            Data& Top() override;
            
            void Pop() override;
            Data TopNPop() override;
            
            void Push(const Data&) override;
            void Push (Data&&) override;


            bool Empty() const noexcept override { return head == 0; }
            ulong Size() const noexcept override { return head; }
            
            void Clear() override { head = 0; Resize(defaultSize); }
            void Resize(ulong newSize) override { if (newSize >= defaultSize) Vector<Data>::Resize(newSize); }
    };
}

#include "stackvec.cpp"
#endif