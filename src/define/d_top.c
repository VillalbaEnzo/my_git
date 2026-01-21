/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** d_top.c
*/

#include "my.h"
#include "struct.h"

top_t *define_top(void)
{
    top_t *t = malloc(sizeof(top_t));

    if (t == NULL)
        return NULL;
    memset(t, 0, sizeof(top_t));
    t->p = malloc(sizeof(p_t));
    memset(t->p, 0, sizeof(p_t));
    t->s = malloc(sizeof(set_t));
    memset(t->s, 0, sizeof(set_t));
    t->inf = init_inf();
    if (t->inf == NULL)
        return NULL;
    t->pros = malloc(sizeof(process_t));
    memset(t->pros, 0, sizeof(process_t));
    t->sys = malloc(sizeof(system_t));
    memset(t->sys, 0, sizeof(system_t));
    return t;
}
