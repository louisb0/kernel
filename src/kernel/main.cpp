#include <stdint.h>
#include <stddef.h>

#include <kernel/multiboot.h>
#include <kernel/allocator.hpp>
#include <kstd/print.hpp>
#include <hal/memory.hpp>


extern "C" void kmain(multiboot_info_t* mbi) {
    if (!(mbi->flags & MULTIBOOT_INFO_MEM_MAP)) {
        kstd::println("No memory map provided");
        return;
    }

    kernel::allocator::instance().initialise(hal::get_heap(mbi));

    int* squares = new int[5];
    int* cubes = new int[5];
    for (int i = 0; i < 5; i++) {
        squares[i] = i * i;
        cubes[i] = i * i * i;
    }

    kstd::println("0x%lx: %u %u %u %u %u", squares, squares[0], squares[1], squares[2], squares[3], squares[4]);
    kstd::println("0x%lx: %u %u %u %u %u", cubes, cubes[0], cubes[1], cubes[2], cubes[3], cubes[4]);
}
