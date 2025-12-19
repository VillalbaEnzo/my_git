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
    if (game->plane_texture)
        sfTexture_destroy(game->plane_texture);
    if (game->tower_texture)
        sfTexture_destroy(game->tower_texture);
}

static void destroy_text(game_t *game)
{
    if (game->time_text->font)
        sfFont_destroy(game->time_text->font);
    if (game->time_text->text)
        sfText_destroy(game->time_text->text);
    free(game->time_text);
}

static void destroy_list(game_t *game)
{
    sprite_list_t *current = game->entities;
    sprite_list_t *next_node = NULL;

    while (current != NULL) {
        next_node = current->next;
        free_sprite_node(current);
        current = next_node;
    }
    game->entities = NULL;
}

void destroy_game(game_t *game)
{
    destroy_general(game);
    destroy_list(game);
    destroy_text(game);
    sfClock_destroy(game->clock);
    free(game);
}
