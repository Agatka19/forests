#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "read.h"

#define ADD "ADD"
#define DEL "DEL"
#define PRINT "PRINT"
#define CHECK "CHECK"

static const u_char *SEPARATORS = (u_char *) "\t\v\f\r ";

bool instruction(u_char *character, int *ret_add, int *ret_del, int *ret_print, int *ret_check) {
    if (character != NULL) {
        *ret_add = strcmp_u(character, (u_char *) ADD);
        *ret_del = strcmp_u(character, (u_char *) DEL);
        *ret_print = strcmp_u(character, (u_char *) PRINT);
        *ret_check = strcmp_u(character, (u_char *) CHECK);
        if (*ret_add == 0 || *ret_check == 0 || *ret_del == 0 || *ret_print == 0)
            return true;
        else return false;
    }
    return false;
}

bool check_ASCII(u_char *character) {
    for (uint i = 0; i < sizeof(character); i++) {
        if (character[i] != 0 && character[i] < 32) {
            return false;
        }
    }
    return true;
}

void read(u_char *character, Tree *forests) {
    if (character == NULL) return;

    int ret_add, ret_del, ret_print, ret_check;
    u_char *character0, *character1, *character2, *character3, *character4;

    character0 = strtok_u(character, SEPARATORS);
    if (character0 == NULL)
        return;
    character1 = character2 = character3 = character4 = NULL;
    if (character0 != NULL) character1 = strtok_u(NULL, SEPARATORS);
    if (character1 != NULL) character2 = strtok_u(NULL, SEPARATORS);
    if (character2 != NULL) character3 = strtok_u(NULL, SEPARATORS);
    if (character3 != NULL) character4 = strtok_u(NULL, SEPARATORS);
    if (character4 != NULL) {
        fprintf(stderr, "ERROR\n");
        return;;
    }

    if (character1 != NULL && !check_ASCII(character1)) {
        fprintf(stderr, "ERROR\n");
        return;
    }

    if (character2 != NULL && !check_ASCII(character2)) {
        fprintf(stderr, "ERROR\n");
        return;
    }

    if (character3 != NULL && !check_ASCII(character3)) {
        fprintf(stderr, "ERROR\n");
        return;
    }

    if (instruction(character0, &ret_add, &ret_del, &ret_print, &ret_check)) {

        if (ret_add == 0) {
            bool exists = false;
            if (character1 == NULL) {
                fprintf(stderr, "ERROR\n");
                return;;
            }
            if (find(forests, character1) != NULL) exists = true;
            Tree f;
            if (exists == false) {
                f = insert(forests, character1);
                f->link = NULL;
            } else f = find(forests, character1);
            Tree trees = f->link;

            if (character2 == NULL) {
                fprintf(stdout, "OK\n");
                return;;
            }
            if (find_in_trees(&f, character2) == NULL) exists = false;
            else exists = true;
            Tree t;
            if (exists == false) {
                t = insert(&trees, character2);
                t->link = NULL;
            } else t = find_in_trees(&f, character2);
            f->link = trees;
            Tree animals = t->link;

            if (character3 == NULL) {
                fprintf(stdout, "OK\n");
                return;;
            }
            if (find_in_trees(&t, character3) == NULL)
                exists = false; //tree 'animals' is a tree linked to tree 't'
            else exists = true;
            if (exists == false) insert(&animals, character3);
            t->link = animals;
            fprintf(stdout, "OK\n");
            return;;
        }

        if (ret_del == 0) {
            if (character1 == NULL) {
                removeAll(*forests);
                *forests = NULL;
                free(*forests);
                fprintf(stdout, "OK\n");
                return;
            }

            Tree f = find(forests, character1);
            if (character2 == NULL) {
                if (f != NULL)
                    removeValue(forests, character1);
                fprintf(stdout, "OK\n");
                return;
            }

            Tree t = find_in_trees(forests, character2);
            if (character3 == NULL) {
                if (t != NULL)
                    removeValue(&(f->link), character2);
                fprintf(stdout, "OK\n");
                return;
            }

            Tree a = find_in_animals(forests, character3);
            if (a != NULL)
                removeValue(&(t->link), character3);
            fprintf(stdout, "OK\n");
            return;
        }

        if (ret_check == 0) {
            if (character1 == NULL) {
                fprintf(stderr, "ERROR\n");
                return;
            }

            Tree f = find(forests, character1);
            if (character2 == NULL) {
                if (*character1 == '*')
                    fprintf(stderr, "ERROR\n");
                else if (f != NULL)
                    fprintf(stdout, "YES\n");
                else
                    fprintf(stdout, "NO\n");
                return;
            }

            Tree t;
            if (*character1 == '*')
                t = find_in_trees((forests), character2);
            else if (f != NULL)
                t = find(&(f->link), character2);
            else t = NULL;
            if (character3 == NULL) {
                if (*character2 == '*')
                    fprintf(stderr, "ERROR\n");
                else if (t != NULL)
                    fprintf(stdout, "YES\n");
                else
                    fprintf(stdout, "NO\n");
                return;
            }

            if (*character3 == '*') {
                fprintf(stderr, "ERROR\n");
                return;
            }
            Tree a;
            if (*character2 != '*') {
                if (f == NULL) {
                    fprintf(stdout, "NO\n");
                    return;
                }
                a = find(&(t->link), character3);
            } else {
                if (*character1 == '*' && *character2 == '*')
                    a = find_in_animals(forests, character3);
                else {
                    if (f == NULL) {
                        fprintf(stdout, "NO\n");
                        return;
                    }
                    a = find_in_trees(&(f->link), character3);
                }
            }
            if (a != NULL)
                fprintf(stdout, "YES\n");
            else
                fprintf(stdout, "NO\n");
            return;
        }

        if (ret_print == 0) {
            if (character1 == NULL) {
                printAll(*forests);
                return;
            }
            if (character2 == NULL) {
                Tree f = find(forests, character1);
                if (f != NULL)
                    printAll(f->link);
                return;
            }

            if (character3 == NULL) {
                Tree t = find_in_trees(forests, character2);
                if (t != NULL)
                    printAll(t->link);
            } else
                fprintf(stderr, "ERROR\n");
            return;
        }


    } else {
        fprintf(stderr, "ERROR\n");
        return;
    }
}

void program(Tree *forests) {
    u_char *buffor = NULL;
    size_t buf_size = 1;
    ssize_t line_size;
    while ((line_size = getline((char **) &buffor, &buf_size, stdin)) >= 0) {
        if (buffor[line_size - 1] == '\n')
            buffor[line_size - 1] = '\0';
        if (buffor[0] == '#' || buffor[0] == '\n' || buffor[0] == 0)
            continue;
        read(buffor, forests);
    }
    free(buffor);
}