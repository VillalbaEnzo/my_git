/*
** EPITECH PROJECT, 2026
** robotfactory
** File description:
** main
*/
#include "op.h"

int main(int ac, char **av)
{
    data_t *to_write = NULL;

    if (ac != 2 || is_file_valid(av[1]) == false)
        return 84;
    to_write = parse_file(av[1]);
    if (!to_write || !to_write->header)
        return 84;
    write_header(to_write);
    return 84;
}
