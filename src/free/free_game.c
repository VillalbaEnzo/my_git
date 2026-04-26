/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** free_game.c
*/

#include "structs.h"
#include "wolf3d.h"

static void free_window(game_t *game)
{
    if (game->window) {
        if (game->window->clock)
            sfClock_destroy(game->window->clock);
        if (game->window->render)
            sfRenderWindow_destroy(game->window->render);
        free(game->window);
    }
}

static void free_ui_menu(game_t *game)
{
    if (game->ui->menu) {
        if (game->ui->menu->bg_sprite)
            sfSprite_destroy(game->ui->menu->bg_sprite);
        if (game->ui->menu->bg_texture)
            sfTexture_destroy(game->ui->menu->bg_texture);
        if (game->ui->menu->cursor_sprite)
            sfSprite_destroy(game->ui->menu->cursor_sprite);
        if (game->ui->menu->cursor_texture)
            sfTexture_destroy(game->ui->menu->cursor_texture);
        free(game->ui->menu);
    }
}

static void free_ui(game_t *game)
{
    if (game->ui) {
        free_ui_menu(game);
        free(game->ui);
    }
}

void free_game(game_t *game)
{
    if (!game)
        return;
    free_window(game);
    free_ui(game);
    free(game);
}
