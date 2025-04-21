#include <stddef.h>
#include <stdint.h>

#include "kstd/print.hpp"

namespace {
    constexpr size_t vga_width = 80;
    constexpr size_t vga_height = 25;
    uint16_t* const vga_buffer = reinterpret_cast<uint16_t*>(0xB8000);

    size_t row = 0;
    size_t col = 0;
}

void kstd::print(const char *s) {
    while (*s != 0) {
        if (*s == '\n') {
            row++;
            col = 0;
            s++;
            continue;
        }

        if (col == vga_width) {
            row++;
            col = 0;
        }

        if (row == vga_height) {
            row = 0;
            col = 0;
        }

        vga_buffer[row * vga_width + col] = *s | 0x0F00;

        s++;
        col++;
    }
}
