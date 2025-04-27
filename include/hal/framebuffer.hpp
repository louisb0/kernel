#pragma once

#include <stddef.h>

namespace hal::framebuffer {
    constexpr size_t WIDTH = 80;
    constexpr size_t HEIGHT = 25;

    void put_char(char c, size_t x, size_t y);
}
