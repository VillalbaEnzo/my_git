/*
** EPITECH PROJECT, 2025
** crocus
** File description:
** free_ret.c
*/

#include "my.h"

int free_ret(char *str, parsing_t *pars, int ret)
{
    if (str)
        free(str);
    if (pars)
        free(pars);
    return ret;
}
