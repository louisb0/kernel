#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>

#include <hal/framebuffer.hpp>
#include <kstd/print.hpp>
#include <kstd/string.hpp>

namespace {
    enum class length_modifier {
        DEFAULT,
        LONG_LONG,
    };
}

static size_t x = 0;
static size_t y = 0;

void kstd::print(char c) {
    if (c == '\n') {
        x = 0;
        y++;
        return;
    }

    if (x == hal::framebuffer::WIDTH) {
        x = 0;
        y++;
    }

    if (y == hal::framebuffer::HEIGHT) {
        x = 0;
        y = 0;
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

            length_modifier modifier = length_modifier::DEFAULT;
            if (*format == 'l') {
                format++;
                if (*format == 'l') {
                    format++;
                    modifier = length_modifier::LONG_LONG;
                } 
            }

            switch (*format) {
            case 'u': {
                uint64_t val = (modifier == length_modifier::LONG_LONG) 
                    ? va_arg(args, long long) 
                    : va_arg(args, unsigned int);

                print_str(itoa(val, 10));
                break;
            }

            case 'x': {
                uint64_t val = (modifier == length_modifier::LONG_LONG) 
                    ? va_arg(args, long long) 
                    : va_arg(args, unsigned int);

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
