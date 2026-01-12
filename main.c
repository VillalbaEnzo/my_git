/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** main.c
*/

#include "my.h"
#include "struct.h"

int main(int ac, char **av)
{
    top_t *t = define_top();

    if (av == NULL || ac == 0 || t == NULL || ac > 7)
        return 84;
    if (parsing_av(av, t) == 84)
        return 84;
    get_infos(t);
    // print_top(t);
    free(t);
    return 0;
}
