#ifndef STACK_HPP
#define STACK_HPP
#include "../container/container.hpp"

namespace lasd {

    template <typename Data>
    class Stack : virtual public ClearableContainer {

    public:

        virtual ~Stack() = default;

        Stack& operator=(const Stack&) = delete;
        Stack& operator=(Stack&&) noexcept = delete;

        bool operator==(const Stack&) const noexcept = delete;
        inline bool operator!=(const Stack&) const noexcept = delete;


        virtual const Data& Top() const = 0; 
        virtual Data& Top() = 0;
        
        virtual void Push(const Data&) = 0;
        virtual void Push(Data&&) = 0; 
        
        virtual void Pop() = 0;
        virtual Data TopNPop() = 0;
    };
}

#endif