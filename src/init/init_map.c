/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1
** File description:
** init_map.c
*/

#include "my.h"

static void set_map_values(map_t *map)
{
    map->width = 20;
    map->height = 20;
    map->angle_x = 0.7853982;
    map->angle_y = 0.5235988;
    map->zoom = 64.0f;
    map->rotation = 0.0f;
    map->offset = (sfVector2f){GAME_WIDTH / 2.0f, 200.0f};
}

static void free_map_arrays(game_t *game, int y)
{
    for (int i = 0; i < y; i++) {
        if (game->map->z_map[i])
            free(game->map->z_map[i]);
        if (game->map->points_2d[i])
            free(game->map->points_2d[i]);
    }
    if (game->map->z_map)
        free(game->map->z_map);
    if (game->map->points_2d)
        free(game->map->points_2d);
    free(game->map);
    game->map = NULL;
}

static void clean_row(game_t *game, int y)
{
    if (game->map->z_map[y])
        free(game->map->z_map[y]);
    if (game->map->points_2d[y])
        free(game->map->points_2d[y]);
    free_map_arrays(game, y);
}

static bool alloc_map_rows(game_t *game)
{
    for (int y = 0; y < game->map->height; y++) {
        game->map->z_map[y] = malloc(game->map->width * sizeof(float));
        game->map->points_2d[y] = malloc(game->map->width * sizeof(sfVector2f));
        if (!game->map->z_map[y] || !game->map->points_2d[y]) {
            clean_row(game, y);
            return false;
        }
        for (int x = 0; x < game->map->width; x++)
            game->map->z_map[y][x] = 0.0f;
    }
    return true;
}

bool init_map(game_t *game)
{
    game->map = malloc(sizeof(map_t));
    if (!game->map)
        return false;
    set_map_values(game->map);
    game->map->z_map = malloc(sizeof(float *) * game->map->height);
    game->map->points_2d = malloc(sizeof(sfVector2f *) * game->map->height);
    if (!game->map->z_map || !game->map->points_2d) {
        free_map_arrays(game, 0);
        return false;
    }
    if (!alloc_map_rows(game))
        return false;
    update_2d_map(game);
    return true;
}
