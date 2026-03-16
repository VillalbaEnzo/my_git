/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** parsing.c
*/

#include "my.h"

static int get_nb_robots(maze_t *maze, char *line)
{
    if (maze->nb_robots != 0)
        return 0;
    if (is_nbr(line) && my_getnbr(line) > 0) {
        maze->nb_robots = my_getnbr(line);
        return 1;
    }
    return -1;
}

static int parse_line(char *line, maze_t *maze, int *type)
{
    int robot_status = get_nb_robots(maze, line);

    if (robot_status == 1)
        return 1;
    if (robot_status == -1)
        return 0;
    if (is_command(line, type))
        return 1;
    if (is_room(line)) {
        if (!add_room(maze, line, *type))
            return 0;
        *type = NORMAL;
        return 1;
    }
    if (is_tunnel(line)) {
        add_tunnel(maze, line);
        return 1;
    }
    return 0;
}

int parsing(char **buf, maze_t *maze)
{
    int type = NORMAL;

    for (int i = 0; buf[i]; i++) {
        if (!parse_line(buf[i], maze, &type))
            break;
    }
    if (!maze->start || !maze->end || maze->nb_robots <= 0)
        return 0;
    return 1;
}
