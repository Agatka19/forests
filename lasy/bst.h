#ifndef BST_H
#define BST_H

#include "struct.h"
#include "library.h"

Tree insert(Tree *, u_char *);

void printAll(Tree);

Tree find(Tree *, u_char *);

Tree find_in_trees(Tree *, u_char *);

Tree find_in_animals(Tree *, u_char *);

void removeValue(Tree *, u_char *);

void removeAll(Tree);

#endif // BST_H

