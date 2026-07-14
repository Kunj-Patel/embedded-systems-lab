#include "custom_string.h"
#include <stdint.h>

/*
  Remember C pointer rules: You cannot directly dereference or do pointer arithmetic on a  void*  because the compiler
  doesn't know how big the underlying data type is (is it 1 byte? 4 bytes?).
  Therefore, your first step inside both functions must be to cast the incoming  void*  pointers to  uint8_t*  (or  char* ), so
  you can loop exactly  n  times and copy byte-by-byte.
 */

void* custom_memcpy(void* dest, const void* src, size_t n) {
    uint8_t* d = (uint8_t*)dest;
    const uint8_t* s = (const uint8_t*)src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

void* custom_memset(void* dest, int c, size_t n) {
    uint8_t* d = (uint8_t*)dest;
    for (size_t i = 0; i < n; i++) {
        d[i] = (uint8_t)c; // Cast the int to uint8_t to ensure only the LSB is used
    }
    return dest;
}
