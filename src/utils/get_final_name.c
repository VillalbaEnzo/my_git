/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-robotfactory-5 [WSL: Ubuntu-24.04]
** File description:
** get_final_name.c
*/

#include "op.h"

char *get_final_name(const char *fn)
{
    char *new_fn;
    int len;

    if (!fn)
        return NULL;
    len = my_strlen(fn);
    if (len < 1)
        return NULL;
    new_fn = malloc(len + 3);
    if (!new_fn)
        return NULL;
    my_strncpy(new_fn, fn, len - 1);
    new_fn[len - 1] = '\0';
    my_strcat(new_fn, "cor");
    return new_fn;
}
