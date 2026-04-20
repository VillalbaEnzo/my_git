/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** free_game.c
*/

#include "structs.h"
#include "wolf3d.h"

static void free_audio(audio_t *audio)
{
    if (audio) {
        if (audio->bg_music)
            sfMusic_destroy(audio->bg_music);
        free(audio);
    }
}

static void free_window(window_t *window)
{
    if (window) {
        if (window->clock)
            sfClock_destroy(window->clock);
        if (window->render)
            sfRenderWindow_destroy(window->render);
        free(window);
    }
}

static void free_ui(ui_t *ui)
{
    if (ui)
        free(ui);
}

void free_game(game_t *game)
{
    free_audio(game->audio);
    free_window(game->window);
    // free_ui(game->ui);
    free(game);
}
