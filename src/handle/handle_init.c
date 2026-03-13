/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** handle_init.c
*/

#include "my.h"

int handle_init(maze_t *maze)
{
    if (!maze)
        return 0;
    init_maze(maze);
    return 1;
}
