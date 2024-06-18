#ifndef STACKLST_HPP
#define STACKLST_HPP
#include "../stack.hpp"
#include "../../list/list.hpp"

namespace lasd {
    
    template <typename Data>
    class StackLst : 
        virtual public Stack<Data>, 
        virtual protected List<Data> {
        
        public:

            StackLst() = default;

            StackLst(const StackLst& stk) { operator=(stk); }
            StackLst(StackLst&& stk) noexcept { operator=(std::move(stk)); }
            
            StackLst(const TraversableContainer<Data>& cntr) : List<Data>(cntr) {}
            StackLst(MappableContainer<Data>&& cntr) : List<Data> (std::move(cntr)) {}

            virtual ~StackLst() = default;

            StackLst& operator=(const StackLst&);
            StackLst& operator=(StackLst&&) noexcept;

            inline bool operator==(const StackLst& stk) const noexcept { return List<Data>::operator==(stk); }
            inline bool operator!=(const StackLst& stk) const noexcept { return !(operator==(stk)); }


            inline const Data& Top() const override { return List<Data>::Front(); }
            inline Data& Top() override { return List<Data>::Front(); }
            
            inline void Push(const Data& d) override { return List<Data>::InsertAtFront(d); }
            inline void Push(Data&& d) override { return List<Data>::InsertAtFront(d); }
            
            inline void Pop() override { return List<Data>::RemoveFromFront(); }
            inline Data TopNPop() override { return List<Data>::FrontNRemove(); }
            
            using List<Data>::Clear;
    };
}

#include "stacklst.cpp"
#endif