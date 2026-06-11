/*
** EPITECH PROJECT, 2025
** crocus
** File description:
** handle_error.c
*/

#include "my.h"

bool handle_error(int argc, parsing_t *pars)
{
    if (argc != 3 && argc != 5)
        return false;
    if (pars->has_s && (!pars->flag_s || !pars->flag_s[0]))
        return false;
    if (!pars->flag_n || !pars->flag_n[0])
        return false;
    for (int i = 0; pars->flag_n[i]; i++)
        if (!isdigit(pars->flag_n[i]))
            return false;
    return true;
}
