#include <stddef.h>
#include <stdint.h>

#include <kstd/memory.hpp>

void *kstd::memcpy(void *dest, const void *src, size_t n) {
    uint8_t *pdest = static_cast<uint8_t*>(dest);
    const uint8_t *psrc = static_cast<const uint8_t*>(src);

    for (size_t i = 0; i < n; i++) {
        pdest[i] = psrc[i];
    }

    return dest;
}

void *kstd::memset(void *s, int c, size_t n) {
    uint8_t *ps = static_cast<uint8_t*>(s);

    for (size_t i = 0; i < n; i++) {
        ps[i] = c;
    }

    return s;
}

void *kstd::memmove(void *dest, const void *src, size_t n) {
    uint8_t *pdest = static_cast<uint8_t*>(dest);
    const uint8_t *psrc = static_cast<const uint8_t*>(src);

    if (src > dest) {
        for (size_t i = 0; i < n; i++) {
            pdest[i] = psrc[i];
        }
    } else {
        for (size_t i = n; i > 0; i--) {
            pdest[i - 1] = psrc[i - 1];
        }
    }

    return dest;
}

int kstd::memcmp(const void *s1, const void *s2, size_t n) {
    const uint8_t *p1 = static_cast<const uint8_t*>(s1);
    const uint8_t *p2 = static_cast<const uint8_t*>(s2);

    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return (p1[i] < p2[i]) ? -1 : 1;
        }
    }

    return 0;
}

extern "C" {
    void *memcpy(void *dest, const void *src, size_t n) {
        return kstd::memcpy(dest, src, n);
    }

    void *memset(void *s, int c, size_t n) {
        return kstd::memset(s, c, n);
    }

    void *memmove(void *dest, const void *src, size_t n) {
        return kstd::memmove(dest, src, n);
    }

    int memcmp(const void *s1, const void *s2, size_t n) {
        return kstd::memcmp(s1, s2, n);
    }
}
