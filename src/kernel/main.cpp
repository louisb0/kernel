#include <stdint.h>
#include <stddef.h>

#include <kernel/multiboot.h>
#include <kstd/print.hpp>

extern "C" void kmain(multiboot_info* boot) {
    if (!(boot->flags & MULTIBOOT_INFO_MEM_MAP)) {
        kstd::println("No memory map provided");
        return;
    }

    multiboot_mmap_entry *entry = reinterpret_cast<multiboot_mmap_entry *>(boot->mmap_addr);
    multiboot_mmap_entry *end = reinterpret_cast<multiboot_mmap_entry *>(boot->mmap_addr + boot->mmap_length);

    while (entry < end) {
        kstd::println("Type: %d", entry->type);
        kstd::println("Address: 0x%x", entry->addr);
        kstd::println("Length: 0x%x", entry->len);
        kstd::println("Size: 0x%d\n", entry->size);

        entry++;
    }
}
