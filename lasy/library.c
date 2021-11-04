#include <string.h>
#include "library.h"

int strcmp_u(const u_char *p1, const u_char *p2) {
    return strcmp((const char *) p1, (const char *) p2);
}

u_char *strtok_u(u_char *s, const u_char *delim) {
    return (u_char *) strtok((char *) s, (const char *) delim);
}

u_char *strcpy_u(u_char *dest, const u_char *source) {
    return (u_char *) strcpy((char *) dest, (const char *) source);
}

size_t strlen_u(const u_char *s) {
    return strlen((const char *) s);
}
