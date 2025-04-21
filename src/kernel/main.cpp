#include <stdint.h>

#include "kstd/print.hpp"
#include "kernel/multiboot.h"

extern "C" void kmain(multiboot_info* boot) {
    kstd::print(reinterpret_cast<const char*>(boot->boot_loader_name));
}
