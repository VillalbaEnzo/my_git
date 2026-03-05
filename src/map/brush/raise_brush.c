/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** raise_brush.c
*/

#include "my.h"

void raise_brush(game_t *game, int center_x, int center_y)
{
    int radius = atoi(game->pl_ui->tb->brush->radius_input);
    float strength = atof(game->pl_ui->tb->brush->strength_input);
    if (radius <= 0) radius = 1;
    if (strength == 0) strength = 1.0;

    for (int y = center_y - radius; y <= center_y + radius; y++) {
        for (int x = center_x - radius; x <= center_x + radius; x++) {
            if (x >= 0 && x < game->map->width && y >= 0 && y < game->map->height) {
                float distance = sqrt(pow(x - center_x, 2) + pow(y - center_y, 2));
                if (distance <= radius) {
                    game->map->z_map[y][x] += strength;
                }
            }
        }
    }
}