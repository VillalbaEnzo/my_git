/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** create_game.c
*/

#include "my.h"

static bool create_window(game_t *game)
{
    sfVideoMode mode = {GAME_WIDTH, GAME_HEIGHT, 32};

    game->window = sfRenderWindow_create(mode, "My_world", sfDefaultStyle,
        NULL);
    if (!game->window)
        return false;
    sfRenderWindow_setFramerateLimit(game->window, 60);
    return true;
}

game_t *create_game(void)
{
    game_t *game = malloc(sizeof(game_t));

    if (!game)
        return NULL;
    init_game(game);
    if (!create_window(game) || !create_background(game))
        return NULL;
    return game;
}
