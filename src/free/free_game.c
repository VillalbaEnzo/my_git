/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5
** File description:
** free_game.c
*/

#include "wolf3d.h"

void free_game(game_t *game)
{
    if (!game)
        return;
    free_window(game);
    free_ui(game);
    free_levels(game->levels);
    free(game->player ? : NULL);
    sfRectangleShape_destroy(game->render_half ? : NULL);
    sfRectangleShape_destroy(game->render_col ? : NULL);
    free(game);
}
