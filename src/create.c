/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31 [WSL: Ubuntu-24.04]
** File description:
** create.c
*/

#include "../include/my.h"

game_t *create_game(void)
{
    game_t *game = malloc(sizeof(game_t));

    if (!game)
        return NULL;
    init(game);
    if (!create_background(game) || !create_window(game)
        || !create_clock(game))
        return NULL;
    return game;
}
