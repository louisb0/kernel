#include <stddef.h>

#include <kstd/string.hpp>

char *kstd::itoa(int value, size_t base) {
    static char buffer[32]{};

    int start = 30;
    if (value == 0) {
        buffer[start--] = '0';
    }

    for (; value && start; start--, value /= base) {
        buffer[start] = "0123456789ABCDEF"[value % base];
    }

    return &buffer[start + 1];
}

