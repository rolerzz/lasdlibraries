#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "../container/linear.hpp"

namespace lasd {
    
    template <typename Data>
    class Vector : 
        virtual public ResizableContainer,
        virtual public LinearContainer<Data> {

        protected:

            using Container::size;
            Data* elements = nullptr;

        public:

            Vector() = default;
            Vector(const ulong);

            Vector(const Vector& vec);
            Vector(Vector&& vec) noexcept { operator=(std::move(vec)); }
            
            Vector(const TraversableContainer<Data>&);
            Vector(MappableContainer<Data>&&);

            virtual ~Vector() { delete[] elements; }

            Vector& operator=(const Vector&);
            Vector& operator=(Vector&&) noexcept;

            using LinearContainer<Data>::operator==;
            using LinearContainer<Data>::operator!=;

            const Data& operator[](const ulong) const override;
            Data& operator[](const ulong) override;


            void Clear() override;
            void Resize(const ulong) override;
    };





    template <typename Data>
    class SortableVector : 
        virtual public Vector<Data>,
        virtual public SortableLinearContainer<Data> {
        
        public:

            SortableVector() = default;
            SortableVector(const ulong size) : Vector<Data>::Vector(size) {}
            SortableVector(const TraversableContainer<Data>& cntr) : Vector<Data>::Vector(cntr) {}
            SortableVector(MappableContainer<Data>&& cntr) : Vector<Data>::Vector(std::move(cntr)) {}

            SortableVector(const SortableVector& cntr) : Vector<Data>::Vector(cntr) {}
            SortableVector(SortableVector&& cntr) noexcept : Vector<Data>::Vector(std::move(cntr)) {}

            virtual ~SortableVector() = default;

            SortableVector& operator=(const SortableVector&);
            SortableVector& operator=(SortableVector&&) noexcept;

            using Vector<Data>::operator[];
    };
}

#include "vector.cpp"
#endif