#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP
#include "traversable.hpp"

namespace lasd {

    template <typename Data>
    class MappableContainer : virtual public TraversableContainer<Data> {
    
        public:

            virtual ~MappableContainer() = default;

            MappableContainer& operator=(const MappableContainer&) = delete;
            MappableContainer& operator=(MappableContainer&&) noexcept = delete;

            bool operator==(const MappableContainer&) const noexcept = delete;
            inline bool operator!=(const MappableContainer&) const noexcept = delete;


            using MapFun = std::function<void(Data&)>;
            virtual void Map(MapFun) = 0;
    };





    template <typename Data>
    class PreOrderMappableContainer : 
        virtual public MappableContainer<Data>, 
        virtual public PreOrderTraversableContainer<Data> {

        public:

            virtual ~PreOrderMappableContainer() = default;

            PreOrderMappableContainer& operator=(const PreOrderMappableContainer&) = delete;
            PreOrderMappableContainer& operator=(PreOrderMappableContainer&&) noexcept = delete;

            bool operator==(const PreOrderMappableContainer&) const noexcept = delete;
            inline bool operator!=(const PreOrderMappableContainer&) const noexcept = delete;


            using typename MappableContainer<Data>::MapFun;
            virtual void PreOrderMap(MapFun) = 0;

            virtual inline void Map(MapFun fun) { PreOrderMap(fun); }
    };





    template <typename Data>
    class PostOrderMappableContainer : 
        virtual public MappableContainer<Data>, 
        virtual public PostOrderTraversableContainer<Data> {

        public:

            virtual ~PostOrderMappableContainer() = default;

            PostOrderMappableContainer& operator=(const PostOrderMappableContainer&) = delete;
            PostOrderMappableContainer& operator=(PostOrderMappableContainer&&) noexcept = delete;

            bool operator==(const PostOrderMappableContainer&) const noexcept = delete;
            inline bool operator!=(const PostOrderMappableContainer&) const noexcept = delete;


            using typename MappableContainer<Data>::MapFun;
            virtual void PostOrderMap(MapFun) = 0;

            virtual inline void Map(MapFun fun) override { PostOrderMap(fun); }
    };





    template <typename Data>
    class InOrderMappableContainer : 
        virtual public MappableContainer<Data>,
        virtual public InOrderTraversableContainer<Data> {

        public:

            virtual ~InOrderMappableContainer() = default;

            InOrderMappableContainer& operator=(const InOrderMappableContainer&) = delete;
            InOrderMappableContainer& operator=(InOrderMappableContainer&&) noexcept = delete;

            bool operator==(const InOrderMappableContainer&) const noexcept = delete;
            inline bool operator!=(const InOrderMappableContainer&) const noexcept = delete;


            using typename MappableContainer<Data>::MapFun;
            virtual void InOrderMap(MapFun) = 0;

            virtual inline void Map(MapFun fun) { InOrderMap(fun); }
    };





    template <typename Data>
    class BreadthMappableContainer : 
        virtual public MappableContainer<Data>, 
        virtual public BreadthTraversableContainer<Data> {

        public:

            virtual ~BreadthMappableContainer() = default;

            BreadthMappableContainer& operator=(const BreadthMappableContainer&) = delete;
            BreadthMappableContainer& operator=(BreadthMappableContainer&&) noexcept = delete;

            bool operator==(const BreadthMappableContainer&) const noexcept = delete;
            inline bool operator!=(const BreadthMappableContainer&) const noexcept = delete;


            using typename MappableContainer<Data>::MapFun;
            virtual void BreadthMap(MapFun) = 0;

            virtual inline void Map(MapFun fun) override { BreadthMap(fun); }
    };
}

#endif