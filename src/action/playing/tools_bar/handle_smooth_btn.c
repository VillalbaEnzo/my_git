/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** handle_lower_btn.c
*/

#include "my.h"

void handle_smooth_btn(game_t *game)
{
    if (!game->mouse_clicked)
        return;
    sfText_setFillColor(game->pl_ui->tb->smooth_btn, sfGreen);
    game->pl_ui->tb->tb_state = SMOOTH;
}
