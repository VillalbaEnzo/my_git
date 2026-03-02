/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** create_raise_btn.c
*/

#include "my.h"

bool create_lower_btn(game_t *game)
{
    game->tb->lower_btn = sfText_create();
    if (!game->tb->lower_btn)
        return false;
    sfText_setString(game->tb->lower_btn, "Lower");
    sfText_setFont(game->tb->lower_btn, game->font);
    sfText_setCharacterSize(game->tb->lower_btn, 30);
    sfText_setPosition(game->tb->lower_btn, (sfVector2f){1725, 800});
    return true;
}
