/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31
** File description:
** plane.c
*/

#include "../../include/my.h"

static void move_one_plane(sprite_list_t *tmp, float dt)
{
    sfVector2f pos = sfSprite_getPosition(tmp->sprite);
    sfVector2f vector = {tmp->end_pos.x - pos.x, tmp->end_pos.y - pos.y};
    float distance = sqrt(vector.x * vector.x + vector.y * vector.y);
    float step = tmp->speed * dt;
    sfVector2f movement = {0.0, 0.0};

    if (distance <= step) {
        sfSprite_setPosition(tmp->sprite, tmp->end_pos);
        tmp->has_arrived = true;
        return;
    }
    movement.x = (vector.x / distance) * step;
    movement.y = (vector.y / distance) * step;
    sfSprite_move(tmp->sprite, movement);
    sfRectangleShape_move(tmp->hitbox, movement);
}

static void del_plane_has_arrived(game_t *game)
{
    sprite_list_t *current = game->entities;
    sprite_list_t *prev = NULL;
    sprite_list_t *to_free = NULL;

    while (current) {
        if (!current->has_arrived && !current->is_destroyed) {
            prev = current;
            current = current->next;
            continue;
        }
        to_free = current;
        if (!prev) {
            game->entities = current->next;
            current = game->entities;
        } else {
            prev->next = current->next;
            current = current->next;
        }
        free_sprite_node(to_free);
    }
}

static void move_plane(game_t *game)
{
    sprite_list_t *tmp = game->entities;

    while (tmp) {
        if (tmp->is_plane && tmp->delay <= game->total_time)
            tmp->has_taken_off = true;
        if (!tmp->has_arrived && tmp->has_taken_off)
            move_one_plane(tmp, game->dt);
        tmp = tmp->next;
    }
}

void handle_plane(game_t *game)
{
    move_plane(game);
    del_plane_has_arrived(game);
}
