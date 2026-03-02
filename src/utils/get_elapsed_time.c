/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** get_elapsed_time.c
*/

#include "my.h"

float get_elapsed_time(game_t *game)
{
    sfTime time = sfClock_getElapsedTime(game->clock);

    return (float) time.microseconds / 1000000.0;;
}
