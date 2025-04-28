#pragma once

#include <stdint.h>

#include <kernel/multiboot.h>

namespace hal {
    struct memory_region {
        uint64_t addr;
        uint64_t len;
    };

    memory_region get_heap(multiboot_info_t* mbi);
}
