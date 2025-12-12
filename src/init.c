/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31 [WSL: Ubuntu-24.04]
** File description:
** init.c
*/

#include "../include/my.h"

void init_sprite_list(sprite_list_t *sprite_list)
{
    sprite_list->start_pos = (sfVector2f){0, 0};
    sprite_list->current_pos = (sfVector2f){0, 0};
    sprite_list->end_pos = (sfVector2f){0, 0};
    sprite_list->is_plane = false;
    sprite_list->has_arrived = false;
    sprite_list->has_taken_off = false;
    sprite_list->delay = 0;
    sprite_list->radius = 0;
    sprite_list->speed = 0.0;
    sprite_list->area = NULL;
    sprite_list->hitbox = NULL;
    sprite_list->sprite = NULL;
    sprite_list->texture = NULL;
    sprite_list->next = NULL;
}

static void init_general(game_t *game)
{
    game->state = START_MENU;
    game->window = NULL;
    game->background_sprite = NULL;
    game->background_texture = NULL;
    game->entities = NULL;
}

void init(game_t *game)
{
    init_general(game);
}
