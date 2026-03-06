/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** parsing.c
*/

#include "my.h"

void parsing(char **buf, maze_t *maze)
{
    int type = NORMAL;

    for (int i = 0; buf[i]; i++) {
        if (is_command(buf[i], &type))
            continue;
        if (is_tunnel(buf[i])) {
            add_tunnel(maze, buf[i]);
            continue;
        }
        if (is_room(buf[i])) {
            add_room(maze, buf[i], type);
            type = NORMAL;
            continue;
        }
        if (maze->nb_robots == 0)
            maze->nb_robots = my_getnbr(buf[i]);
    }
}
