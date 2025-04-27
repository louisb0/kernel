#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>

#include "kstd/print.hpp"
#include <hal/framebuffer.hpp>
#include <kstd/string.hpp>

static size_t x = 0;
static size_t y = 0;

void kstd::print(char c) {
    if (c == '\n') {
        x = 0;
        y++;
    }

    if (x == hal::framebuffer::WIDTH) {
        y++;
        x = 0;
    }

    if (y == hal::framebuffer::HEIGHT) {
        y = 0;
        x = 0;
    }

    hal::framebuffer::put_char(c, x++, y);
}

void print_str(const char *s) {
    while (*s != '\0') {
        kstd::print(*s++);
    }
}

void kstd::vprint(const char *format, va_list args) {
    while (*format) {
        if (*format == '%') {
            format++;

            switch (*format) {
            case 'd': {
                int val = va_arg(args, int);
                if (val < 0) {
                    print('-');
                    val = -val;
                }

                print_str(itoa(val, 10));
                break;
            }

            case 'x': {
                int val = va_arg(args, int);
                if (val < 0) {
                    print('-');
                    val = -val;
                }

                print_str(itoa(val, 16));
                break;
            }

            case 's': {
                const char* s = va_arg(args, const char*);
                print_str(s);
                break;
            }

            default:
                print('%');
                print(*format);
                break;
            }
        } else {
            print(*format);
        }

        format++;
    }
}

void kstd::print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprint(format, args);
    va_end(args);
}

void kstd::println(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprint(format, args);
    va_end(args);
    print('\n');
}
