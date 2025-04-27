#include <stddef.h>

#include <kstd/string.hpp>

char *kstd::itoa(int value, size_t base) {
    static char buffer[32]{};

    int i = 30;
    for (; value && i; i--, value /= base) {
        buffer[i] = "0123456789ABCDEF"[value % base];
    }

    return &buffer[i + 1];
}

