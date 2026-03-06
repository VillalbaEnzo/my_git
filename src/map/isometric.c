/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** isometric.c
*/

#include "my.h"

sfVector2f project_iso_point(int x, int y, float z, map_t *map)
{
    sfVector2f point2d = {0, 0};
    float cx = map->width / 2.0f;
    float cy = map->height / 2.0f;
    float rx = (x - cx) * cos(map->rotation) - (y - cy) * sin(map->rotation);
    float ry = (x - cx) * sin(map->rotation) + (y - cy) * cos(map->rotation);

    point2d.x = (cos(map->angle_x) * rx - cos(map->angle_x) * ry)
        * map->zoom + map->offset.x;
    point2d.y = (sin(map->angle_y) * ry + sin(map->angle_y) * rx - z)
        * map->zoom + map->offset.y;
    return point2d;
}

void update_2d_map(game_t *game)
{
    for (int y = 0; y < game->map->height; y++) {
        for (int x = 0; x < game->map->width; x++) {
            game->map->points_2d[y][x] = project_iso_point(x, y,
                game->map->z_map[y][x], game->map);
        }
    }
}
