/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** parsing.c
*/

#include "my.h"
#include "struct.h"

static int verify_arg(char **av)
{
    for (int i = 0; av[i]; i++) {
        if (av[i][0] == '-' && av[i + 1][0] == '-') {
            my_perror("Error: Missing arguments\n");
            print_helper();
            return 84;
        }
    }
    return 0;
}

int parsing_av(char **av, top_t *t)
{
    if (verify_arg(av) == 84)
        return 84;
    for (int i = 0; av[i]; i++) {
        if (my_strcmp("-h", av[i]) == 0)
            print_helper();
        if (my_strcmp("-U", av[i]) == 0) {
            t->p->username = 1;
            t->s->username = my_strdup(av[i + 1]);
        }
        if (my_strcmp("-n", av[i]) == 0) {
            t->p->frames = 1;
            t->s->frames = my_getnbr(av[i + 1]);
        }
        if (my_strcmp("-d", av[i]) == 0) {
            t->p->secondes = 1;
            t->s->secondes = my_getfloatnbr(av[i + 1]);
        }
    }
    return 0;
}
