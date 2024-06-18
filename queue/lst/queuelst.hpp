#ifndef QUEUELST_HPP
#define QUEUELST_HPP
#include "../queue.hpp"
#include "../../list/list.hpp"

namespace lasd {

    template <typename Data>
    class QueueLst :
        virtual public Queue<Data>,
        virtual protected List<Data> {

        public:

            QueueLst() = default;

            QueueLst(const QueueLst& que) { operator=(que); }
            QueueLst(QueueLst&& que) noexcept { operator=(std::move(que)); }

            QueueLst(const TraversableContainer<Data>& cntr) : List<Data>(cntr) {}
            QueueLst(MappableContainer<Data>&& cntr) : List<Data> (std::move(cntr)) {}

            virtual ~QueueLst() = default;

            QueueLst& operator=(const QueueLst&);
            QueueLst& operator=(QueueLst&&) noexcept;

            inline bool operator==(const QueueLst& que) const noexcept { return List<Data>::operator==(que); }
            inline bool operator!=(const QueueLst& que) const noexcept { return !(operator==(que)); }


            inline const Data& Head() const override { return List<Data>::Front(); }
            inline Data& Head() override { return List<Data>::Front(); }
            
            inline void Enqueue(const Data& d) override { List<Data>::InsertAtBack(d); }
            inline void Enqueue(Data&& d) override { List<Data>::InsertAtBack(std::move(d)); }

            inline void Dequeue() override { List<Data>::RemoveFromFront(); }
            inline Data HeadNDequeue() override { return List<Data>::FrontNRemove(); }

            using List<Data>::Clear;
    };
}

#include "queuelst.cpp"
#endif