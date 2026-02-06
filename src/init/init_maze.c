/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** init_maze.c
*/

#include "my.h"

void init_maze(maze_t *maze)
{
    maze->start = NULL;
    maze->end = NULL;
    maze->nb_robots = 0;
    maze->rooms = NULL;
}
