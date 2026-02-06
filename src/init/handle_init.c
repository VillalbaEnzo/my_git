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
    all->room = malloc(sizeof(room_t));
    if (!all->room) {
        free(all->maze);
        return 0;
    }
    all->neighbor = malloc(sizeof(neighbor_t));
    if (!all->neighbor) {
        free(all->maze);
        free(all->room);
        return 0;
    }
    init_maze(all->maze);
    init_room(all->room);
    init_neighbor(all->neighbor);
    return 1;
}
