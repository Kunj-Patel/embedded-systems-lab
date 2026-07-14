#ifndef CUSTOM_STRING_H
#define CUSTOM_STRING_H

#include <stddef.h> // required for size_t

void* custom_memcpy(void *dest, const void *src, size_t n);
void* custom_memset(void *s, int c, size_t n);

#endif // CUSTOM_STRING_H