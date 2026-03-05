/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** handle_map_click.c
*/

#include "my.h"

static sfVector2i get_mouse_map_pos(game_t *game, sfVector2f mouse_pos)
{
    sfVector2i map_pos = {-1, -1};
    float min_dist = -1.0f;
    sfVector2f p;
    float dx = 0.0;
    float dy = 0.0;
    float dist = 0.0;

    for (int y = 0; y < game->map->height; y++) {
        for (int x = 0; x < game->map->width; x++) {
            p = game->map->points_2d[y][x];
            dx = p.x - mouse_pos.x;
            dy = p.y - mouse_pos.y;
            dist = (dx * dx) + (dy * dy);
            if (min_dist == -1.0f || dist < min_dist) {
                min_dist = dist;
                map_pos.x = x;
                map_pos.y = y;
            }
        }
    }
    return map_pos;
}

void handle_map_click(game_t *game)
{
    if (!sfMouse_isButtonPressed(sfMouseLeft))
        return;

    sfVector2i pixel_pos = sfMouse_getPositionRenderWindow(game->window);
    sfVector2f mouse_pos = sfRenderWindow_mapPixelToCoords(game->window, pixel_pos, NULL);
    sfVector2i map_pos = get_mouse_map_pos(game, mouse_pos);

    if (map_pos.x >= 0 && map_pos.x < game->map->width &&
        map_pos.y >= 0 && map_pos.y < game->map->height) {
        apply_brush(game, map_pos.x, map_pos.y);
    }
}