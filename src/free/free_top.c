/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** free_top.c
*/

#include "my.h"
#include "struct.h"

void free_top(top_t *t)
{
    if (!t)
        return;
    if (t->p)
        free(t->p);
    if (t->s) {
        if (t->s->username)
            free(t->s->username);
        free(t->s);
    }
    if (t->inf) {
        if (t->inf->processes)
            free(t->inf->processes);
        free(t->inf);
    }
    if (t->pros)
        free(t->pros);
    if (t->sys)
        free(t->sys);
    free(t);
}
