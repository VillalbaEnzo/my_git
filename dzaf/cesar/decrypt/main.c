/*
** EPITECH PROJECT, 2025
** next
** File description:
** main.c
*/

#include "my.h"

static bool is_nbr(char *str)
{
    for (int i = 0; str[i]; i++)
        if (!isdigit(str[i]))
            return false;
    return true;
}

int main(int argc, char **argv)
{
    char *str = NULL;

    if (argc != 3)
        return 84;
    if (!is_nbr(argv[2]))
        return 84;
    str = read_file(argv[1]);
    if (!str)
        return 84;
    handle_prog(str, -my_getnbr(argv[2]));
    printf("%s", str);
    free(str);
    return 0;
}
