/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** create_raise_btn.c
*/

#include "my.h"

bool create_raise_btn(game_t *game)
{
    game->tb->raise_btn = sfText_create();
    if (!game->tb->raise_btn)
        return false;
    sfText_setString(game->tb->raise_btn, "Raise");
    sfText_setFont(game->tb->raise_btn, game->font);
    sfText_setCharacterSize(game->tb->raise_btn, 30);
    sfText_setPosition(game->tb->raise_btn, (sfVector2f){1725, 900});
    return true;
}
