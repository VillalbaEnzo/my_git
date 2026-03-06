/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** map_events.c
*/

#include "my.h"

static void handle_zoom(game_t *game, sfEvent event)
{
    if (event.type != sfEvtMouseWheelScrolled)
        return;
    if (event.mouseWheelScroll.delta > 0)
        game->map->zoom += 2.0f;
    if (event.mouseWheelScroll.delta < 0 && game->map->zoom > 5.0f)
        game->map->zoom -= 2.0f;
    update_2d_map(game);
}

static void handle_move(game_t *game, sfEvent event)
{
    if (event.type != sfEvtKeyPressed)
        return;
    if (event.key.code == sfKeyUp)
        game->map->offset.y += 20.0f;
    if (event.key.code == sfKeyDown)
        game->map->offset.y -= 20.0f;
    if (event.key.code == sfKeyLeft)
        game->map->offset.x += 20.0f;
    if (event.key.code == sfKeyRight)
        game->map->offset.x -= 20.0f;
    update_2d_map(game);
}

static void handle_rotation(game_t *game, sfEvent event)
{
    if (event.type == sfEvtKeyPressed) {
        if (event.key.code == sfKeyA)
            game->map->rotation += 0.1f;
        if (event.key.code == sfKeyD)
            game->map->rotation -= 0.1f;
        update_2d_map(game);
    }
}

void handle_map_events(game_t *game, sfEvent event)
{
    if (game->state != PLAYING)
        return;
    handle_zoom(game, event);
    handle_move(game, event);
    handle_rotation(game, event);
}
