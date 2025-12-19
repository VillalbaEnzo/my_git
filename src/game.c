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

    sfRenderWindow_clear(game->window, sfBlack);
    sfRenderWindow_drawSprite(game->window, game->background_sprite, NULL);
    sfRenderWindow_drawText(game->window, game->time_text->text, NULL);
    while (tmp) {
        if (!tmp->is_plane && game->show_hitbox)
            sfRenderWindow_drawCircleShape(game->window, tmp->area, NULL);
        if (tmp->has_taken_off && tmp->is_plane && game->show_hitbox)
            sfRenderWindow_drawRectangleShape(game->window, tmp->hitbox, NULL);
        if (tmp->is_plane && game->show_sprites && tmp->has_taken_off)
            sfRenderWindow_drawSprite(game->window, tmp->sprite, NULL);
        if (!tmp->is_plane && game->show_sprites)
            sfRenderWindow_drawSprite(game->window, tmp->sprite, NULL);
        tmp = tmp->next;
    }
}

static bool is_game_finished(game_t *game)
{
    sprite_list_t *tmp = game->entities;

    while (tmp) {
        if (tmp->is_plane)
            return false;
        tmp = tmp->next;
    }
    return true;
}

// static void game_start(game_t *game)
// {
//     sfImage_
// }

static void game_in_play(game_t *game)
{
    char *time;

    game->dt = sfTime_asSeconds(sfClock_restart(game->clock));
    game->total_time += game->dt;
    time = seconds_to_time((int)game->total_time);
    sfText_setString(game->time_text->text, time);
    free(time);
    handle_plane(game);
    check_collision(game);
    draw_entities(game);
    sfRenderWindow_display(game->window);
}

// static void game_pause(game_t *game)
// {

// }

void game_loop(game_t *game)
{
    game->total_time = 0.0;
    while (sfRenderWindow_isOpen(game->window)) {
        if (is_game_finished(game)) {
            sfRenderWindow_close(game->window);
            continue;
        }
        if (game->in_play)
            game_in_play(game);
        manage_events(game);
    }
}
