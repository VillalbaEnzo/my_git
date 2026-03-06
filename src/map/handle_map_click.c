/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** handle_map_click.c
*/

#include "my.h"

static void check_cl(sfVector2i *map_pos, float *min_d, float dist,
    sfVector2i *cur)
{
    if (*min_d == -1.0f || dist < *min_d) {
        *min_d = dist;
        map_pos->x = cur->x;
        map_pos->y = cur->y;
    }
}

static sfVector2i get_mouse_map_pos(game_t *game, const sfVector2f *mouse_pos)
{
    sfVector2i map_pos = {-1, -1};
    float min_dist = -1.0f;
    sfVector2f p = {0, 0};
    float dist = 0;
    sfVector2i cur = {0, 0};

    for (int y = 0; y < game->map->height; y++) {
        for (int x = 0; x < game->map->width; x++) {
            p = game->map->points_2d[y][x];
            dist = pow(p.x - mouse_pos->x, 2) + pow(p.y - mouse_pos->y, 2);
            cur.x = x;
            cur.y = y;
            check_cl(&map_pos, &min_dist, dist, &cur);
        }
    }
    return map_pos;
}

void handle_map_click(game_t *game)
{
    sfVector2i p_pos;
    sfVector2f m_pos;
    sfVector2i map_pos;

    if (!sfMouse_isButtonPressed(sfMouseLeft))
        return;
    p_pos = sfMouse_getPositionRenderWindow(game->window);
    m_pos = sfRenderWindow_mapPixelToCoords(game->window, p_pos, NULL);
    map_pos = get_mouse_map_pos(game, &m_pos);
    if (map_pos.x >= 0 && map_pos.x < game->map->width &&
        map_pos.y >= 0 && map_pos.y < game->map->height) {
        apply_brush(game, map_pos.x, map_pos.y);
    }
}
