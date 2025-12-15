/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31 [WSL: Ubuntu-24.04]
** File description:
** destroy.c
*/

#include "../include/my.h"

static void destroy_general(game_t *game)
{
    if (game->window)
        sfRenderWindow_destroy(game->window);
    if (game->background_texture)
        sfTexture_destroy(game->background_texture);
    if (game->background_sprite)
        sfSprite_destroy(game->background_sprite);
}

static void destroy_list(game_t *game)
{
    sprite_list_t *tmp = game->entities;

    if (game->entities->sprite)
        sfSprite_destroy(game->entities->sprite);
    if (game->entities->area)
        sfCircleShape_destroy(game->entities->area);
    if (game->entities->hitbox)
        sfRectangleShape_destroy(game->entities->hitbox);
    if (game->entities->texture)
        sfTexture_destroy(game->entities->texture);
    game->entities = game->entities->next;
    free(tmp);
}

void destroy_game(game_t *game)
{
    destroy_general(game);
    while (game->entities != NULL)
        destroy_list(game);
    free(game->entities);
    sfClock_destroy(game->clock);
    free(game);
}
