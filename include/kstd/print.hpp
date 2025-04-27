#pragma once

#include <stdarg.h>

namespace kstd {
    void print(char s);
    void vprint(const char *format, va_list args);
    void print(const char *format, ...);
    void println(const char *format, ...);
}
