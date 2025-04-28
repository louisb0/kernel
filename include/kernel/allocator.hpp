#pragma once

#include <stddef.h>
#include <stdint.h>

#include <hal/memory.hpp>

namespace kernel {
    class allocator {
    public:
        static allocator& instance() {
            static allocator instance;
            return instance;
        }

        void initialise(const hal::memory_region& region) {
            _free = static_cast<intptr_t>(region.addr);
            _limit = static_cast<intptr_t>(region.addr + region.len);
        }

        void* allocate(size_t size);

    private:
        intptr_t _free{};
        intptr_t _limit{};
    };
}
