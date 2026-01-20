/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** init_functions.c
*/

#include "struct.h"
#include <stdlib.h>
#include "my.h"

set_t *init_set(void)
{
    set_t *s = malloc(sizeof(set_t));
    int i;
    char *ptr;

    if (s == NULL)
        return NULL;
    ptr = (char *)s;
    for (i = 0; i < (int)sizeof(set_t); i++)
        ptr[i] = 0;
    s->frames = 0;
    s->username = NULL;
    s->secondes = 0.0;
    return s;
}
