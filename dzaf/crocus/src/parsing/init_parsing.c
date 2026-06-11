/*
** EPITECH PROJECT, 2025
** crocus
** File description:
** init_parsing.c
*/

#include "my.h"

parsing_t *init_parsing(void)
{
    parsing_t *pars = malloc(sizeof(parsing_t));

    if (!pars)
        return NULL;
    pars->flag_n = NULL;
    pars->flag_s = NULL;
    pars->has_s = false;
    return pars;
}
