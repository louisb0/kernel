#include <stdint.h>
#include <stddef.h>

#include <kernel/multiboot.h>
#include <kstd/print.hpp>

extern "C" void kmain(multiboot_info_t* boot) {
    if (!(boot->flags & MULTIBOOT_INFO_MEM_MAP)) {
        kstd::println("No memory map provided");
        return;
    }

    multiboot_memory_map_t* entry = reinterpret_cast<multiboot_memory_map_t*>(boot->mmap_addr);
    multiboot_memory_map_t* end = reinterpret_cast<multiboot_memory_map_t*>(boot->mmap_addr + boot->mmap_length);

    while (entry < end) {
        kstd::println("Type: %u, Address: 0x%llx, Length: 0x%llx", entry->type, entry->addr, entry->len);

        entry++;
    }
}
