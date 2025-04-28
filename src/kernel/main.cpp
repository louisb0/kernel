#include <stdint.h>
#include <stddef.h>

#include <kernel/multiboot.h>
#include <kstd/print.hpp>
#include <hal/memory.hpp>

extern "C" void kmain(multiboot_info_t* mbi) {
    if (!(mbi->flags & MULTIBOOT_INFO_MEM_MAP)) {
        kstd::println("No memory map provided");
        return;
    }

    kstd::println("heap: 0x%llx", hal::get_heap(mbi).len);
}
