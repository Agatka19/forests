#ifndef STRUCT_H
#define STRUCT_H

#include "library.h"

struct Node;
typedef struct Node *Tree;

struct Node {
    Tree left, right, link;
    u_char *word;
};

#endif // STRUCT_H

