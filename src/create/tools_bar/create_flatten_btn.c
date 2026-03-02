/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** create_raise_btn.c
*/

#include "my.h"

bool create_flatten_btn(game_t *game)
{
    game->tb->flatten_btn = sfText_create();
    if (!game->tb->flatten_btn)
        return false;
    sfText_setString(game->tb->flatten_btn, "Flatten");
    sfText_setFont(game->tb->flatten_btn, game->font);
    sfText_setCharacterSize(game->tb->flatten_btn, 30);
    sfText_setPosition(game->tb->flatten_btn, (sfVector2f){1725, 850});
    return true;
}
