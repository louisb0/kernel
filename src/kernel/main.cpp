#include <stdint.h>
#include <stddef.h>

#include "kstd/print.hpp"
#include "kernel/multiboot.h"

extern "C" void kmain(multiboot_info* boot) {
    if (!(boot->flags & MULTIBOOT_INFO_MEM_MAP)) {
        kstd::print("No memory map provided\n");
        return;
    }

    multiboot_mmap_entry *entry = reinterpret_cast<multiboot_mmap_entry *>(boot->mmap_addr);
    multiboot_mmap_entry *end = reinterpret_cast<multiboot_mmap_entry *>(boot->mmap_addr + boot->mmap_length);

    while (entry < end) {
        kstd::print("Type: ");
        kstd::print(entry->type);
        kstd::print("\n");

        kstd::print("Addr: 0x");
        kstd::print(entry->addr, true);
        kstd::print("\n");

        kstd::print("Length: 0x");
        kstd::print(entry->len, true);
        kstd::print("\n");

        kstd::print("Size: ");
        kstd::print(entry->size);
        kstd::print("\n\n");

        entry++;
    }
}
