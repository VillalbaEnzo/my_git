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

static bool init_brush(game_t *game)
{
    game->pl_ui->tb->brush = malloc(sizeof(brush_t));
    if (!game->pl_ui->tb->brush)
        return false;
    game->pl_ui->tb->brush->radius_box = NULL;
    game->pl_ui->tb->brush->radius_input = NULL;
    game->pl_ui->tb->brush->radius_label = NULL;
    game->pl_ui->tb->brush->radius_pos = 0;
    game->pl_ui->tb->brush->radius_text = NULL;
    game->pl_ui->tb->brush->strength_box = NULL;
    game->pl_ui->tb->brush->strength_input = NULL;
    game->pl_ui->tb->brush->strength_label = NULL;
    game->pl_ui->tb->brush->strength_pos = 0;
    game->pl_ui->tb->brush->strength_text = NULL;
    return true;
}

static bool init_tools_bar(game_t *game)
{
    game->pl_ui->tb = malloc(sizeof(tools_bar_t));
    if (!game->pl_ui->tb)
        return false;
    if (!init_brush(game)) {
        free(game->pl_ui->tb);
        game->pl_ui->tb = NULL;
        return false;
    }
    game->pl_ui->tb->flatten_btn = NULL;
    game->pl_ui->tb->lower_btn = NULL;
    game->pl_ui->tb->raise_btn = NULL;
    game->pl_ui->tb->smooth_btn = NULL;
    game->pl_ui->ui_state = LOWER;
    return true;
}

static void init_game_null(game_t *game)
{
    game->window = NULL;
    game->clock = NULL;
    game->bg = NULL;
    game->music = NULL;
    game->font = NULL;
    game->map = NULL;
    game->pl_ui = NULL;
    game->start_menu = NULL;
    game->textures = NULL;
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

static bool init_textures(game_t *game)
{
    game->textures = malloc(sizeof(texture_t));
    if (!game->textures)
        return false;
    game->textures->dirt_text = NULL;
    game->textures->stone_text = NULL;
    game->textures->grass_text = NULL;
    game->textures->snow_text = NULL;
    game->textures->secret_text = NULL;
    return true;
}

bool init_game(game_t *game)
{
    init_game_null(game);
    game->state = START_MENU;
    game->is_running = false;
    game->font = sfFont_createFromFile(FONT_PATH);
    if (!game->font)
        return false;
    if (!init_bg(game) || !init_playing_ui(game) ||
        !init_start_menu(game) || !init_map(game) ||
        !init_textures(game))
        return false;
    return true;
}
