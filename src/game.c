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

static void move_one_plane(sprite_list_t *tmp, float dt)
{
    sfVector2f vector = {0.0, 0.0};
    sfVector2f movement = {0.0, 0.0};
    float total_dist = 0.0;

    vector.x = tmp->end_pos.x - tmp->start_pos.x;
    vector.y = tmp->end_pos.y - tmp->start_pos.y;
    total_dist = my_sqrt((vector.x * vector.x) + (vector.y * vector.y));
    movement.x = (vector.x / total_dist) * tmp->speed * dt;
    movement.y = (vector.y / total_dist) * tmp->speed * dt;
    sfSprite_move(tmp->sprite, movement);
}

static void move_plane(game_t *game)
{
    float dt = sfTime_asSeconds(sfClock_getElapsedTime(game->clock));
    sprite_list_t *tmp = game->entities;

    while (tmp) {
        if (tmp->is_plane && tmp->delay <= dt)
            move_one_plane(tmp, dt);
        tmp = tmp->next;
    }
}

void game_loop(game_t *game)
{
    sfClock_restart(game->clock);
    while (sfRenderWindow_isOpen(game->window)) {
        manage_events(game);
        sfRenderWindow_drawSprite(game->window, game->background_sprite, NULL);
        draw_entities(game);
        move_plane(game);
        sfRenderWindow_display(game->window);
    }
}
