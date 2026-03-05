/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** apply_brush.c
*/

#include "my.h"

void apply_brush(game_t *game, int target_x, int target_y)
{
    if (game->pl_ui->ui_state == RAISE)
        raise_brush(game, target_x, target_y);
    else if (game->pl_ui->ui_state == LOWER)
        lower_brush(game, target_x, target_y);
    else if (game->pl_ui->ui_state == FLATTEN)
        flatten_brush(game, target_x, target_y);
    else if (game->pl_ui->ui_state == SMOOTH)
        smooth_brush(game, target_x, target_y);
    update_2d_map(game);
}