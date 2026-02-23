/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** handle_init.c
*/

#include "my.h"

int handle_init(all_t *all)
{
    all->maze = malloc(sizeof(maze_t));
    if (!all->maze)
        return 0;
    all->room = NULL;
    all->neighbor = NULL;
    init_maze(all->maze);
    return 1;
}
