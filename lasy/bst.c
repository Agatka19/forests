#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bst.h"

Tree insert(Tree *t, u_char *x) {
    if (*t == NULL) {
        *t = (Tree) malloc(sizeof(struct Node));
        if (*t == NULL) exit(1);
        (*t)->word = malloc(strlen_u(x) + 1);
        strcpy_u((*t)->word, x);
        (*t)->left = (*t)->right = (*t)->link = NULL;
        return *t;
    }
    const int cmp = strcmp_u((*t)->word, x);
    if (cmp > 0)
        return insert(&((*t)->left), x);
    if (cmp < 0)
        return insert(&((*t)->right), x);
    return *t;
}

void printAll(Tree t) {
    if (t != NULL) {
        printAll(t->left);
        if (t->word != NULL) printf("%s\n", t->word);
        printAll(t->right);
    }
}

Tree find(Tree *t, u_char *word) {
    if (*t == NULL)
        return NULL;

    const int cmp = strcmp_u((*t)->word, word);
    if (cmp > 0)
        return find((&(*t)->left), word);
    if (cmp < 0)
        return find((&(*t)->right), word);
    return (*t);
}

Tree find_in_trees(Tree *t, u_char *word) {
    if (*t == NULL)
        return *t;

    Tree tmp = find(&(*t)->link, word);
    if (tmp == NULL)
        tmp = find_in_trees(&(*t)->left, word);
    if (tmp == NULL)
        tmp = find_in_trees(&(*t)->right, word);
    return tmp;
}

Tree find_in_animals(Tree *t, u_char *word) {
    if (*t == NULL)
        return *t;

    Tree tmp = NULL;
    if ((*t)->link != NULL)
        tmp = find_in_trees(&((*t)->link), word);
    if (tmp == NULL)
        tmp = find_in_animals(&((*t)->left), word);
    if (tmp == NULL)
        tmp = find_in_animals(&((*t)->right), word);
    return tmp;
}

Tree *findMin(Tree *t) {
    if ((*t)->left == NULL)
        return t;
    return findMin(&(*t)->left);
}

void removeValue(Tree *treePtr, u_char *x) {
    Tree t = *treePtr;
    if (t == NULL) return;
    const int cmp = strcmp_u(t->word, x);
    if (cmp > 0)
        return removeValue(&t->left, x);
    if (cmp < 0)
        return removeValue(&t->right, x);
    if (t->right == NULL) {
        *treePtr = t->left;
    } else {
        Tree *rightMinPtr = findMin(&t->right);
        Tree rightMin = *rightMinPtr;
        *rightMinPtr = rightMin->right;
        *treePtr = rightMin;
        (*treePtr)->left = t->left;
        (*treePtr)->right = t->right;
    }
    removeAll(t->link);
    free(t->word);
    free(t);
}

void removeAll(Tree t) {
    if (t != NULL) {
        removeAll(t->link);
        removeAll(t->left);
        removeAll(t->right);
        t = NULL;
        free(t);
    }
}