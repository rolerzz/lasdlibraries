#ifndef TESTABLE_HPP
#define TESTABLE_HPP
#include "container.hpp"

namespace lasd {

    template <typename Data>
    class TestableContainer : virtual public Container {

        public:
            
            virtual ~TestableContainer() = default;

            TestableContainer& operator=(const TestableContainer&) = delete;
            TestableContainer& operator=(TestableContainer&&) noexcept = delete;

            bool operator==(const TestableContainer&) const noexcept = delete;
            inline bool operator!=(const TestableContainer&) const noexcept = delete;


            virtual bool Exists(const Data&) const noexcept = 0;
    };
}

#endif