#include <stddef.h>
#include <stdint.h>

#include <hal/framebuffer.hpp>

static uint16_t* const buffer = reinterpret_cast<uint16_t*>(0xB8000);

void hal::put_char(char c, size_t x, size_t y) {
    buffer[y * FRAME_WIDTH + x] = c | 0x0F00;
}
