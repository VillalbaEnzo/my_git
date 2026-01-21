/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** d_p.c
*/

#include "struct.h"
#include "stdlib.h"

p_t *init_p(void)
{
    p_t *p = malloc(sizeof(p_t));
    int i;
    char *ptr;

    if (p == NULL)
        return NULL;
    ptr = (char *)p;
    for (i = 0; i < (int)sizeof(p_t); i++)
        ptr[i] = 0;
    p->frames = 0;
    p->username = 0;
    p->secondes = 0;
    return p;
}
