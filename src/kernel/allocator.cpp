#include <stddef.h>

#include <kernel/allocator.hpp>

void* kernel::allocator::allocate(size_t size) {
    if (size > static_cast<size_t>(_limit - _free)) {
        return nullptr;
    }

    void* allocation = reinterpret_cast<void*>(_free);
    _free += size;
    return allocation;
}
