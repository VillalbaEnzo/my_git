/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** create_raise_btn.c
*/

#include "my.h"

bool create_smooth_btn(game_t *game)
{
    game->pl_ui->tb->smooth_btn = sfText_create();
    if (!game->pl_ui->tb->smooth_btn)
        return false;
    sfText_setString(game->pl_ui->tb->smooth_btn, "Smooth");
    sfText_setFont(game->pl_ui->tb->smooth_btn, game->font);
    sfText_setCharacterSize(game->pl_ui->tb->smooth_btn, 30);
    sfText_setPosition(game->pl_ui->tb->smooth_btn, (sfVector2f){1725, 950});
    return true;
}
