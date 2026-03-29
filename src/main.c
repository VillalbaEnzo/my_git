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
    FILE *fstream = NULL;

    if (ac != 2 || is_file_valid(av[1]) == false)
        return 84;
    to_write = malloc(sizeof(data_t));
    if (!to_write)
        return 84;
    fstream = fopen(av[1], "r");
    to_write->header = parse_header(fstream);
    if (to_write->header == NULL)
        return 84;
    return 84;
}
