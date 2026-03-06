/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** destroy_map.c
*/

#include "my.h"

void destroy_map(game_t *game)
{
    if (!game || !game->map)
        return;
    for (int y = 0; y < game->map->height; y++) {
        if (game->map->z_map[y])
            free(game->map->z_map[y]);
        if (game->map->points_2d[y])
            free(game->map->points_2d[y]);
    }
    if (game->map->z_map)
        free(game->map->z_map);
    if (game->map->points_2d)
        free(game->map->points_2d);
    free(game->map);
}
