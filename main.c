/*
** EPITECH PROJECT, 2025
** A-maze-d
** File description:
** main.c
*/

#include "../include/my.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char **buf;
    all_t *all = malloc(sizeof(all_t));

    if (!all)
        return 84;
    buf = load_input();
    if (!buf) {
        free(all);
        return 84;
    }
    if (!handle_init(all))
        return 84;
    parsing(buf, all);
    free_double_buf(buf);
    return 0;
}
