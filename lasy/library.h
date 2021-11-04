#ifndef LIBRARY_H
#define LIBRARY_H

#include <stddef.h>

typedef unsigned char u_char;

int strcmp_u(const u_char *, const u_char *);

u_char *strtok_u(u_char *, const u_char *);

u_char *strcpy_u(u_char *, const u_char *);

size_t strlen_u(const u_char *);

#endif // LIBRARY_H

