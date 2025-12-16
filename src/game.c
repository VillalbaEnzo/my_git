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

void game_loop(game_t *game)
{
    char *time;

    game->total_time = 0.0;
    while (sfRenderWindow_isOpen(game->window)) {
        game->dt = sfTime_asSeconds(sfClock_restart(game->clock));
        game->total_time += game->dt;
        time = unsigned_int_to_str((int)game->total_time);
        sfText_setString(game->time_text->text, time);
        free(time);
        manage_events(game);
        handle_plane(game);
        check_collision(game);
        sfRenderWindow_clear(game->window, sfBlack);
        sfRenderWindow_drawSprite(game->window, game->background_sprite, NULL);
        sfRenderWindow_drawText(game->window, game->time_text->text, NULL);
        draw_entities(game);
        sfRenderWindow_display(game->window);
    }
}
