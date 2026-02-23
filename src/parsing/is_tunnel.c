/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** is_tunnel.c
*/

#include "my.h"

int is_tunnel(char *line)
{
    int space = 0;
    int hyphen = 0;

    if (my_strlen(line) < 3)
        return 0;
    for (int i = 0; line[i]; i++) {
        if (line[i] == ' ')
            space = 1;
        if (i != 0 && line[i] == '-' && line[i + 1] && line[i + 1] != '\0')
            hyphen += 1;
    }
    if (!space && hyphen == 1)
        return 1;
    return 0;
}
