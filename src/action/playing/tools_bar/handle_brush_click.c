/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** handle_brush_click.c
*/

#include "my.h"

void handle_brush_click(game_t *game)
{
    sfRectangleShape *radius_box = game->pl_ui->tb->brush->radius_box;
    sfRectangleShape *strength_box = game->pl_ui->tb->brush->strength_box;
    sfVector2i pixel_pos;
    sfVector2f mouse;
    sfFloatRect r_bounds;
    sfFloatRect s_bounds;

    if (!game->mouse_clicked)
        return;
    pixel_pos = sfMouse_getPositionRenderWindow(game->window);
    mouse = sfRenderWindow_mapPixelToCoords(game->window, pixel_pos, NULL);
    r_bounds = sfRectangleShape_getGlobalBounds(radius_box);
    s_bounds = sfRectangleShape_getGlobalBounds(strength_box);
    if (sfFloatRect_contains(&r_bounds, mouse.x, mouse.y))
        game->pl_ui->ui_state = INPUT_RADIUS;
    else if (sfFloatRect_contains(&s_bounds, mouse.x, mouse.y))
        game->pl_ui->ui_state = INPUT_STRENGTH;
}