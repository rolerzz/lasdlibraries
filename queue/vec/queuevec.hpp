#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP
#include "../queue.hpp"
#include "../../vector/vector.hpp"
#define defaultSize 12UL

namespace lasd {

    template <typename Data>
    class QueueVec :
        virtual public Queue<Data>, 
        virtual protected Vector<Data> {

    protected:

        ulong head = 0;
        ulong tail = 0;
        ulong numElem = 0;
        using Vector<Data>::size;
        using Vector<Data>::elements;

    public:

        QueueVec() : Vector<Data>(defaultSize) {}

        QueueVec(const QueueVec& que) { operator=(que); }
        QueueVec(QueueVec&& que) noexcept { operator=(std::move(que)); }

        QueueVec(const TraversableContainer<Data>&);
        QueueVec(MappableContainer<Data>&&) noexcept;

        virtual ~QueueVec() = default;
    
        QueueVec<Data>& operator=(const QueueVec<Data>&);
        QueueVec<Data>& operator=(QueueVec<Data>&&) noexcept;

        bool operator==(const QueueVec<Data>&) const noexcept;
        inline bool operator!=(const QueueVec<Data>& que) const noexcept { return !(operator==(que)); }


        const Data& Head() const override;
        Data& Head() override;

        void Dequeue() override;
        Data HeadNDequeue() override;

        void Enqueue(const Data&) override;
        void Enqueue(Data&&) override;


        bool Empty() const noexcept override { return numElem == 0; }
        ulong Size() const noexcept override { return numElem; }
        
        void Clear() override;
        void Resize(ulong) override;
    };
}

#include "queuevec.cpp"
#endif