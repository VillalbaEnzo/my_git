/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** handle_brush_click.c
*/

#include "my.h"

void handle_brush_click(game_t *game, sfVector2f *mouse_pos)
{
    sfRectangleShape *r_box = game->pl_ui->tb->brush->radius_box;
    sfRectangleShape *s_box = game->pl_ui->tb->brush->strength_box;
    sfFloatRect r_bounds = sfRectangleShape_getGlobalBounds(r_box);
    sfFloatRect s_bounds = sfRectangleShape_getGlobalBounds(s_box);

    if (!game->mouse_clicked)
        return;
    if (sfFloatRect_contains(&r_bounds, mouse_pos->x, mouse_pos->y))
        game->pl_ui->ui_state = INPUT_RADIUS;
    else if (sfFloatRect_contains(&s_bounds, mouse_pos->x, mouse_pos->y))
        game->pl_ui->ui_state = INPUT_STRENGTH;
}
