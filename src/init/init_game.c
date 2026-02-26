/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** init_game.c
*/

#include "my.h"

void init_game(game_t *game)
{
    game->bg = malloc(sizeof(game->bg));
    game->bg->bg_sp = NULL;
    game->bg->bg_tx = NULL;
    game->window = NULL;
    game->clock = NULL;
    game->is_running = false;
    game->music = NULL;
}
