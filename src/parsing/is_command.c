/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** is_command.c
*/

#include "my.h"

int is_command(char *line, int *type)
{
    if (my_strcmp(line, "##start") == 0) {
        *type = 1;
        return 1;
    }
    if (my_strcmp(line, "##end") == 0) {
        *type = 2;
        return 1;
    }
    return 0;
}
