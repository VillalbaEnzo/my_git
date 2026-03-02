/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** init_game.c
*/

#include "my.h"

static bool init_bg(game_t *game)
{
    game->bg = malloc(sizeof(bg_t));
    if (!game->bg)
        return false;
    game->bg->bg_sp = NULL;
    game->bg->bg_tx = NULL;
    return true;
}

static bool init_tools_bar(game_t *game)
{
    game->pl_ui->tb = malloc(sizeof(tools_bar_t));
    if (!game->pl_ui->tb)
        return false;
    game->pl_ui->tb->flatten_btn = NULL;
    game->pl_ui->tb->lower_btn = NULL;
    game->pl_ui->tb->raise_btn = NULL;
    game->pl_ui->tb->smooth_btn = NULL;
    game->pl_ui->tb->tb_state = LOWER;
    return true;
}

static bool init_start_menu_btn(game_t *game)
{
    game->start_menu->start_btn = malloc(sizeof(button_t));
    if (!game->start_menu->start_btn)
        return false;
    game->start_menu->quit_btn = malloc(sizeof(button_t));
    if (!game->start_menu->quit_btn) {
        free(game->start_menu->start_btn);
        return false;
    }
    game->start_menu->load_btn = malloc(sizeof(button_t));
    if (!game->start_menu->load_btn) {
        free(game->start_menu->start_btn);
        free(game->start_menu->quit_btn);
        return false;
    }
    return true;
}

static bool init_start_menu(game_t *game)
{
    game->start_menu = malloc(sizeof(menu_t));
    if (!game->start_menu)
        return false;
    if (!init_start_menu_btn(game)) {
        free(game->start_menu);
        return false;
    }
    return true;
}

static bool init_playing_ui(game_t *game)
{
    game->pl_ui = malloc(sizeof(playing_ui_t));
    if (!game->pl_ui)
        return false;
    game->pl_ui->menu_btn = NULL;
    game->pl_ui->save_btn = NULL;
    if (!init_tools_bar(game)) {
        free(game->pl_ui);
        return false;
    }
    return true;
}

bool init_game(game_t *game)
{
    game->state = START_MENU;
    game->window = NULL;
    game->clock = NULL;
    game->is_running = false;
    game->music = NULL;
    game->font = sfFont_createFromFile("assets/font/DelaGothicOne.ttf");
    if (!game->font)
        return false;
    if (!init_bg(game))
        return false;
    if (!init_playing_ui(game))
        return false;
    if (!init_start_menu(game)) {
        free(game->bg);
        return false;
    }
    return true;
}
