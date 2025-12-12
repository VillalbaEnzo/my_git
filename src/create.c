/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31 [WSL: Ubuntu-24.04]
** File description:
** create.c
*/

#include "../include/my.h"

static bool create_window(game_t *game)
{
    sfVideoMode mode = {GAME_WIDTH, GAME_HEIGHT, 32};

    game->window = sfRenderWindow_create(mode, "MyRadar", sfDefaultStyle,
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
    init(game);
    if (!create_background(game) || !create_window(game))
        return NULL;
    return game;
}
