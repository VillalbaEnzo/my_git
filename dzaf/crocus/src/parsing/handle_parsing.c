/*
** EPITECH PROJECT, 2025
** crocus
** File description:
** parsing.c
*/

#include "my.h"

void handle_parsing(char **argv, parsing_t *pars)
{
    for (int i = 0; argv[i]; i++) {
        if (strcmp(argv[i], "-n") == 0 && argv[i + 1])
            pars->flag_n = argv[i + 1];
        if (strcmp(argv[i], "-s") == 0 && argv[i + 1]) {
            pars->has_s = true;
            pars->flag_s = argv[i + 1];
        }
    }
}
