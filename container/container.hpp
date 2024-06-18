#ifndef CONTAINER_HPP
#define CONTAINER_HPP
#include <stdexcept>

namespace lasd {

    using ulong = unsigned long;

    class Container {

        protected:

            ulong size = 0;
            Container() = default;

        public:

            virtual ~Container() = default;

            Container& operator=(const Container&) = delete;
            Container& operator=(Container&&) noexcept = delete;

            bool operator==(const Container&) const noexcept = delete;
            inline bool operator!=(const Container&) const noexcept = delete;


            virtual bool Empty() const noexcept { return size == 0; }
            virtual ulong Size() const noexcept { return size; }
    };





    class ClearableContainer : virtual public Container {

        public:

            virtual ~ClearableContainer() = default;

            ClearableContainer& operator=(const ClearableContainer&) = delete;
            ClearableContainer& operator=(ClearableContainer&&) noexcept = delete;

            bool operator==(const ClearableContainer&) const noexcept = delete;
            inline bool operator!=(const ClearableContainer&) const noexcept = delete;


            virtual void Clear() { size = 0; }
    };





    class ResizableContainer : virtual public ClearableContainer {

        public:

            virtual ~ResizableContainer() = default;

            ResizableContainer& operator=(const ResizableContainer&) = delete;
            ResizableContainer& operator=(ResizableContainer&&) noexcept = delete;

            bool operator==(const ResizableContainer&) const noexcept = delete;
            inline bool operator!=(const ResizableContainer&) const noexcept = delete;


            virtual void Resize(ulong newSize) { size = newSize; }
            virtual inline void Clear() override { Resize(0); }
    };
}

#endif