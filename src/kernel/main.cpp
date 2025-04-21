#include <stdint.h>

static uint16_t* const vga_buffer = reinterpret_cast<uint16_t*>(0xB8000);

extern "C" void kmain() {
    vga_buffer[0] = 'h' | 0x0F00;
    vga_buffer[1] = 'i' | 0x0F00;
}
