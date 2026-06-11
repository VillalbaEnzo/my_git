/*
** EPITECH PROJECT, 2025
** crocus
** File description:
** create_string.c
*/

#include "my.h"

static char *no_s_flag(parsing_t *pars)
{
    size_t len = strlen(pars->flag_n);
    char *ret = malloc(sizeof(char) * (len + 1));

    if (!ret)
        return NULL;
    for (size_t i = 0; i < len; i++)
        ret[i] = '0';
    ret[len] = '\0';
    return ret;
}

static char *s_flag(parsing_t *pars)
{
    size_t len_str = strlen(pars->flag_s);
    size_t len_nbr = strlen(pars->flag_n);
    char *ret = malloc(sizeof(char) * (len_nbr + 1));

    if (!ret)
        return NULL;
    for (size_t i = 0; i < len_nbr; i++)
        ret[i] = pars->flag_s[(pars->flag_n[i] - '0') % len_str];
    return ret;
}

char *create_string(parsing_t *pars)
{
    char *ret = NULL;

    if (!pars->has_s)
        ret = no_s_flag(pars);
    else
        ret = s_flag(pars);
    if (!ret)
        return NULL;
    return ret;
}
