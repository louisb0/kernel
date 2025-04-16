#include <stdint.h>
#include <stddef.h>

static uint16_t* const vga_buffer = reinterpret_cast<uint16_t*>(0xB8000);

extern "C" void kmain() {}
