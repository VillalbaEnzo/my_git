/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** init_map.c
*/

#include "my.h"

static void free_map_arrays(game_t *game, int y)
{
    for (int i = 0; i < y; i++) {
        free(game->map->z_map[i]);
        free(game->map->points_2d[i]);
    }
    free(game->map->z_map);
    free(game->map->points_2d);
    free(game->map);
    game->map = NULL;
}

static bool alloc_map_rows(game_t *game)
{
    for (int y = 0; y < game->map->height; y++) {
        game->map->z_map[y] = calloc(game->map->width, sizeof(float));
        game->map->points_2d[y] = malloc(sizeof(sfVector2f) * game->map->width);
        if (!game->map->z_map[y] || !game->map->points_2d[y]) {
            free_map_arrays(game, y);
            return false;
        }
    }
    return true;
}

bool init_map(game_t *game)
{
    game->map = malloc(sizeof(map_t));
    if (!game->map)
        return false;
    game->map->width = 200;
    game->map->height = 200;
    game->map->angle_x = 0.7853982;
    game->map->angle_y = 0.5235988;
    game->map->zoom = 64.0f;
    game->map->rotation = 0.0f;
    game->map->offset = (sfVector2f){GAME_WIDTH / 2.0f, 200.0f};
    game->map->z_map = malloc(sizeof(float *) * game->map->height);
    game->map->points_2d = malloc(sizeof(sfVector2f *) * game->map->height);
    if (!game->map->z_map || !game->map->points_2d || !alloc_map_rows(game)) {
        free_map_arrays(game, 0);
        return false;
    }
    update_2d_map(game);
    return true;
}
