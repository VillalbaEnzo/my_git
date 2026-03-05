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
    sfVector2i mouse = sfMouse_getPositionRenderWindow(game->window);
    sfFloatRect r_bounds = sfRectangleShape_getGlobalBounds(radius_box);
    sfFloatRect s_bounds = sfRectangleShape_getGlobalBounds(strength_box);

    if (!game->mouse_clicked)
        return;
    if (sfFloatRect_contains(&r_bounds, mouse.x, mouse.y))
        game->pl_ui->ui_state = INPUT_RADIUS;
    else if (sfFloatRect_contains(&s_bounds, mouse.x, mouse.y))
        game->pl_ui->ui_state = INPUT_STRENGTH;
}
