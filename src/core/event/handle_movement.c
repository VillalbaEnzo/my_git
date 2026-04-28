/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5
** File description:
** handle_movement.c
*/

#include "wolf3d.h"

static void move_forward_back(game_t *game, map_t *map, int dir)
{
    player_t *p = game->player;
    double speed = p->move_speed * game->window->dt * dir;
    double nx = p->pos.x + p->dir.x * speed;
    double ny = p->pos.y + p->dir.y * speed;

    if (map->grid[(int)p->pos.y][(int)nx] == 0)
        p->pos.x = nx;
    if (map->grid[(int)ny][(int)p->pos.x] == 0)
        p->pos.y = ny;
}

static void rotate(game_t *game, int dir)
{
    player_t *p = game->player;
    double speed = p->rot_speed * game->window->dt * dir;
    double old_dx = p->dir.x;
    double old_px = p->plane.x;

    p->dir.x = p->dir.x * cos(speed) - p->dir.y * sin(speed);
    p->dir.y = old_dx * sin(speed) + p->dir.y * cos(speed);
    p->plane.x = p->plane.x * cos(speed) - p->plane.y * sin(speed);
    p->plane.y = old_px * sin(speed) + p->plane.y * cos(speed);
}

void handle_movement(game_t *game, sfEvent event)
{
    level_t *level = game->levels[game->active_level];

    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyZ)
        move_forward_back(game, level->map, 1);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyS)
        move_forward_back(game, level->map, -1);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyQ)
        rotate(game, -1);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyD)
        rotate(game, 1);
}
