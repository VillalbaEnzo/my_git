/*
** EPITECH PROJECT, 2025
** next
** File description:
** main.c
*/

#include "my.h"

int main(int argc, char **argv)
{
    char *str = NULL;

    if (argc != 4 || !is_num_from_str(argv[3]))
        return 84;
    if ((strcmp(argv[1], "-f") != 0) && (strcmp(argv[1], "-s") != 0)) {
        write(2, "bad flags\n", 10);
        return 84;
    }
    if (strcmp(argv[1], "-f") == 0)
        str = read_file(argv[2]);
    else str = strdup(argv[2]);
    if (!str)
        return 84;
    handle_prog(str, my_getnbr(argv[3]));
    if (!write_file(str))
        return 84;
    free(str);
    return 0;
}
