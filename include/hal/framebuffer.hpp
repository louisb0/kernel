#pragma once

#include <stddef.h>

namespace hal {
    constexpr size_t FRAME_WIDTH = 80;
    constexpr size_t FRAME_HEIGHT = 25;

    void put_char(char c, size_t x, size_t y);
}
