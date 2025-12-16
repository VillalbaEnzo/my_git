/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31
** File description:
** clock.c
*/

#include "../../include/my.h"

bool create_clock(game_t *game)
{
    game->clock = sfClock_create();
    if (!game->clock)
        return false;
    return true;
}
