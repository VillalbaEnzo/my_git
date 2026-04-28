/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5
** File description:
** init_player.c
*/

#include "wolf3d.h"

player_t *init_player(void)
{
    player_t *player = malloc(sizeof(player_t));

    if (!player)
        return NULL;
    player->pos = (sfVector2f){2.0, 2.0};
    player->dir = (sfVector2f){1.0, 0.0};
    player->plane = (sfVector2f){0.0, 0.66};
    player->move_speed = 3.0;
    player->rot_speed = 2.0;
    return player;
}
