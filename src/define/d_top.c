/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** d_top.c
*/

#include "my.h"
#include "struct.h"

static p_t *define_parsing(void)
{
    p_t *p = malloc(sizeof(p_t));

    if (p == NULL)
        return NULL;
    p->frames = 0;
    p->username = 0;
    p->secondes = 0;
    return p;
}

static set_t *define_set(void)
{
    set_t *s = malloc(sizeof(set_t));

    if (s == NULL)
        return NULL;
    s->frames = 0;
    s->username = NULL;
    s->secondes = 0.0;
    return s;
}

static int init_top_components(top_t *t)
{
    t->inf = init_inf();
    if (t->inf == NULL)
        return 84;
    t->pros = init_process();
    if (t->pros == NULL)
        return 84;
    t->sys = init_system();
    if (t->sys == NULL)
        return 84;
    return 0;
}

static int init_top_parsing_and_set(top_t *t)
{
    t->p = define_parsing();
    if (t->p == NULL) {
        free_top(t);
        return 84;
    }
    t->s = define_set();
    if (t->s == NULL) {
        free_top(t);
        return 84;
    }
    return 0;
}

top_t *define_top(void)
{
    top_t *t = malloc(sizeof(top_t));

    if (t == NULL)
        return NULL;
    if (init_top_parsing_and_set(t) != 0)
        return NULL;
    if (init_top_components(t) != 0)
        return (void *)84;
    return t;
}
