/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** create_menu_btn.c
*/

#include "my.h"

bool create_menu_btn(game_t *game)
{
    game->pl_ui->menu_btn = sfText_create();
    if (!game->pl_ui->menu_btn)
        return false;
    sfText_setString(game->pl_ui->menu_btn, "Menu");
    sfText_setFont(game->pl_ui->menu_btn, game->font);
    sfText_setCharacterSize(game->pl_ui->menu_btn, 30);
    sfText_setPosition(game->pl_ui->menu_btn, (sfVector2f){20, 20});
    return true;
}
