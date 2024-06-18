#ifndef LINEAR_HPP
#define LINEAR_HPP
#include "mappable.hpp"

namespace lasd {

    template <typename Data>
    class LinearContainer : 
        virtual public PreOrderMappableContainer<Data>,
        virtual public PostOrderMappableContainer<Data> {

        protected: using Container::size;

        public:

            virtual ~LinearContainer() = default;

            LinearContainer& operator=(const LinearContainer&) = delete;
            LinearContainer& operator=(LinearContainer&&) noexcept = delete;

            bool operator==(const LinearContainer&) const noexcept;
            inline bool operator!=(const LinearContainer& cntr) const noexcept { return !(operator==(cntr)); }

            virtual const Data& operator[](ulong) const = 0;
            virtual Data& operator[](ulong) = 0;


            const Data& Front() const;
            Data& Front();

            const Data& Back() const;
            Data& Back();


            using typename TraversableContainer<Data>::TraverseFun;
            inline void Traverse(TraverseFun) const override;

            inline void PreOrderTraverse(TraverseFun) const override;
            inline void PostOrderTraverse(TraverseFun) const override;


            using typename MappableContainer<Data>::MapFun;
            inline void Map(MapFun) override;

            inline void PreOrderMap(MapFun) override;
            inline void PostOrderMap(MapFun) override;
    };





    template <typename Data>
    class SortableLinearContainer : virtual public LinearContainer<Data> {

        protected: using Container::size;

        public:

            virtual ~SortableLinearContainer() = default;

            SortableLinearContainer& operator=(const SortableLinearContainer&) = delete;
            SortableLinearContainer& operator=(SortableLinearContainer&&) noexcept = delete;

            using LinearContainer<Data>::operator==;
            using LinearContainer<Data>::operator!=;
            
            using LinearContainer<Data>::operator[];


            virtual void Sort() noexcept;

        protected:
        
            void QuickSort(ulong, ulong) noexcept;
            ulong Partition(ulong, ulong) noexcept;
    };
}

#include "linear.cpp"
#endif