/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** init_game.c
*/

#include "my.h"

void init_game(game_t *game)
{
    game->bg = malloc(sizeof(bg_t));
    game->bg->bg_sp = NULL;
    game->bg->bg_tx = NULL;
    game->state = START_MENU;
    game->window = NULL;
    game->clock = NULL;
    game->is_running = false;
    game->music = NULL;
    game->start_menu = malloc(sizeof(menu_t));
    game->start_menu->start_btn = malloc(sizeof(button_t));
    game->start_menu->quit_btn = malloc(sizeof(button_t));
    game->start_menu->load_btn = malloc(sizeof(button_t));
}
