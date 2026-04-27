/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** free_game.c
*/

#include "structs.h"
#include "wolf3d.h"

void free_audio(audio_t *audio)
{
    if (!audio)
        return;
    if (audio->music)
        sfMusic_destroy(audio->music);
    if (audio->sfx)
        sfSound_destroy(audio->sfx);
    if (audio->buffer)
        sfSoundBuffer_destroy(audio->buffer);
    free(audio);
}

static void free_window(game_t *game)
{
    if (!game->window)
        return;
    if (game->window->clock)
        sfClock_destroy(game->window->clock);
    if (game->window->render)
        sfRenderWindow_destroy(game->window->render);
    free(game->window);
}

static void free_ui_setting(game_t *game)
{
    if (!game || !game->ui || !game->ui->settings)
        return;
    if (game->ui->settings->bg_sprite)
        sfSprite_destroy(game->ui->settings->bg_sprite);
    if (game->ui->settings->bg_texture)
        sfTexture_destroy(game->ui->settings->bg_texture);
    if (game->ui->settings->cursor_sprite)
        sfSprite_destroy(game->ui->settings->cursor_sprite);
    if (game->ui->settings->cursor_texture)
        sfTexture_destroy(game->ui->settings->cursor_texture);
    for (int i = 0; i < SET_COUNT; i++) {
        if (game->ui->settings->btn_texts[i])
            sfText_destroy(game->ui->settings->btn_texts[i]);
    }
    for (int i = 0; i < 2; i++) {
        if (game->ui->settings->slider_bg[i])
            sfRectangleShape_destroy(game->ui->settings->slider_bg[i]);
        if (game->ui->settings->slider_fill[i])
            sfRectangleShape_destroy(game->ui->settings->slider_fill[i]);
    }
    free(game->ui->settings);
}

static void free_ui_menu(game_t *game)
{
    if (!game || !game->ui || !game->ui->menu)
        return;
    if (game->ui->menu->bg_sprite)
        sfSprite_destroy(game->ui->menu->bg_sprite);
    if (game->ui->menu->bg_texture)
        sfTexture_destroy(game->ui->menu->bg_texture);
    if (game->ui->menu->cursor_sprite)
        sfSprite_destroy(game->ui->menu->cursor_sprite);
    if (game->ui->menu->cursor_texture)
        sfTexture_destroy(game->ui->menu->cursor_texture);
    for (int i = 0; i < BTN_COUNT; i++) {
        if (game->ui->menu->btn_texts[i])
            sfText_destroy(game->ui->menu->btn_texts[i]);
    }
    free(game->ui->menu);
}

static void free_ui(game_t *game)
{
    if (!game->ui)
        return;
    if (game->ui->font)
        sfFont_destroy(game->ui->font);
    free_ui_menu(game);
    free_ui_setting(game);
    free_audio(game->ui->music);
    for (int i = 0; i < SFX_UI_COUNT; i++)
        free_audio(game->ui->sfx[i]);
    free(game->ui);
}

void free_game(game_t *game)
{
    if (!game)
        return;
    free_window(game);
    free_ui(game);
    free(game);
}
