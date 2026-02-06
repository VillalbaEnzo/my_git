/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** is_comment.c
*/

#include "my.h"

int is_comment(char *line)
{
    if (my_strlen(line) < 2)
        return 0;
    if (line[0] == '#' && line[1] != '#')
        return 1;
    return 0;
}
