/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5
** File description:
** init_game.c
*/

#include "wolf3d.h"

game_t *init_game(void)
{
    game_t *game = calloc(1, sizeof(game_t));

    game->window = init_window();
    game->ui = game->window ? init_ui() : NULL;
    game->levels = game->ui ? init_levels() : NULL;
    game->player = game->levels ? init_player() : NULL;
    game->render_half = game->player ? sfRectangleShape_create() : NULL;
    game->render_col = game->render_half ? sfRectangleShape_create() : NULL;
    if (!game->render_col) {
        free_game(game);
        return NULL;
    }
    return game;
}
