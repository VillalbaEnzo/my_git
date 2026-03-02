/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** terraforming.c
*/

#include "my.h"

static float get_distance(sfVector2i mouse_pos, sfVector2f point)
{
    return sqrt(pow(mouse_pos.x - point.x, 2) + pow(mouse_pos.y - point.y, 2));
}

static void apply_tool(game_t *game, int y, int x)
{
    tools_bar_state_t tool = game->pl_ui->tb->tb_state;

    if (tool == RAISE) {
        game->map->z_map[y][x] += 1.0f;
    } else if (tool == LOWER) {
        game->map->z_map[y][x] -= 1.0f;
    } else if (tool == FLATTEN) {
        game->map->z_map[y][x] = 0.0f;
    }
}

void handle_terraforming(game_t *game)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(game->window);
    float distance = 0.0f;
    float radius = 20.0f;

    for (int y = 0; y < game->map->height; y++) {
        for (int x = 0; x < game->map->width; x++) {
            distance = get_distance(mouse, game->map->points_2d[y][x]);
            if (distance < radius) {
                apply_tool(game, y, x);
                update_2d_map(game);
                return;
            }
        }
    }
}
