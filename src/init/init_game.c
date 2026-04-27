/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** init_game.c
*/

#include "structs.h"
#include "wolf3d.h"

game_t *init_game(void)
{
    game_t *game = malloc(sizeof(game_t));

    if (!game)
        return NULL;
    game->window = NULL;
    game->ui = NULL;
    game->state = STATE_MENU;
    game->window = init_window();
    if (!game->window) {
        free_game(game);
        return NULL;
    }
    game->ui = init_ui();
    if (!game->ui) {
        free_game(game);
        return NULL;
    }
    return game;
}
