/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** destroy_game.c
*/

#include "my.h"

void destroy_start_menu(game_t *game)
{
    if (game->start_menu->start_btn)
        sfRectangleShape_destroy(game->start_menu->start_btn->rect);
    if (game->start_menu->start_btn->texture)
        sfTexture_destroy(game->start_menu->start_btn->texture);
    if (game->start_menu->load_btn)
        sfRectangleShape_destroy(game->start_menu->load_btn->rect);
    if (game->start_menu->load_btn->texture)
        sfTexture_destroy(game->start_menu->load_btn->texture);
    if (game->start_menu->quit_btn)
        sfRectangleShape_destroy(game->start_menu->quit_btn->rect);
    if (game->start_menu->quit_btn->texture)
        sfTexture_destroy(game->start_menu->quit_btn->texture);
    free(game->start_menu->start_btn);
    free(game->start_menu->load_btn);
    free(game->start_menu->quit_btn);
    free(game->start_menu);
}

void destroy_bg(game_t *game)
{
    if (game->bg->bg_sp)
        sfSprite_destroy(game->bg->bg_sp);
    if (game->bg->bg_tx)
        sfTexture_destroy(game->bg->bg_tx);
    free(game->bg);
}

void destroy_game(game_t *game)
{
    destroy_bg(game);
    destroy_start_menu(game);
    if (game->window)
        sfRenderWindow_destroy(game->window);
    free(game);
}
