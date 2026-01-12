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
    free(t->p);
    free(t->s);
    free(t);
}
