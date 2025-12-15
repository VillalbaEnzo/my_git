/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31 [WSL: Ubuntu-24.04]
** File description:
** game.c
*/

#include "../include/my.h"

static void draw_entities(game_t *game)
{
    sprite_list_t *tmp = game->entities;

    while (tmp != NULL) {
        if (!tmp->is_plane) {
            sfRenderWindow_drawSprite(game->window, tmp->sprite, NULL);
            sfRenderWindow_drawCircleShape(game->window, tmp->area, NULL);
        } else {
            sfRenderWindow_drawSprite(game->window, tmp->sprite, NULL);
            sfRenderWindow_drawRectangleShape(game->window, tmp->hitbox, NULL);
        }
        tmp = tmp->next;
    }
}


static void move_plane(game_t *game)
{
    float time_elapsed = sfTime_asSeconds(sfClock_getElapsedTime(game->clock));
    float distance = game->entities->speed * time_elapsed;
    sfVector2f offset = {distance, 0.0};
    sprite_list_t *tmp = game->entities;

    while (!tmp) {
        if (tmp->delay < time_elapsed) {
            tmp = tmp->next;
            return;
        }
        if (tmp->has_arrived) {
            tmp = tmp->next;
            return;
        }
        if (game->entities->sprite == NULL)
            return;
        sfSprite_move(game->entities->sprite, offset);
    }
}

void game_loop(game_t *game)
{
    while (sfRenderWindow_isOpen(game->window)) {
        sfClock_restart(game->clock);
        manage_events(game);
        sfRenderWindow_drawSprite(game->window, game->background_sprite, NULL);
        draw_entities(game);
        move_plane(game);
        sfRenderWindow_display(game->window);
    }
}
