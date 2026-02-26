/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** create_background.c
*/

#include "my.h"

bool create_background(game_t *game)
{
    game->bg->bg_sp = sfSprite_create();
    if (!game->bg->bg_sp)
        return false;
    game->bg->bg_tx = sfTexture_createFromFile(BG_PATH, NULL);
    if (!game->bg->bg_sp)
        return false;
    sfSprite_setTexture(game->bg->bg_sp, game->bg->bg_tx, sfTrue);
    return true;
}
