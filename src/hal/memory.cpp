#include <hal/memory.hpp>

#include <kernel/multiboot.h>

hal::memory_region hal::get_heap(multiboot_info_t* mbi) {
    hal::memory_region heap{};

    multiboot_memory_map_t* entry = reinterpret_cast<multiboot_memory_map_t*>(mbi->mmap_addr);
    multiboot_memory_map_t* end = reinterpret_cast<multiboot_memory_map_t*>(mbi->mmap_addr + mbi->mmap_length);
    for (; entry < end; entry++) {
        if (entry->type != MULTIBOOT_MEMORY_AVAILABLE) {
            continue;
        }

        if (entry->len > heap.len) {
            heap.addr = entry->addr;
            heap.len = entry->len;
        }
    }

    return heap;
}
