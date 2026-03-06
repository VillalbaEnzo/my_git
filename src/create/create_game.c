/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** create_game.c
*/

#include "my.h"

static bool create_textures(game_t *game)
{
    game->textures->dirt_text = sfTexture_createFromFile(DIRT_TEXT, NULL);
    game->textures->grass_text = sfTexture_createFromFile(GRASS_TEXT, NULL);
    game->textures->snow_text = sfTexture_createFromFile(SNOW_TEXT, NULL);
    game->textures->stone_text = sfTexture_createFromFile(STONE_TEXT, NULL);
    game->textures->secret_text = sfTexture_createFromFile(SECRET_TEXT, NULL);
    if (!game->textures->dirt_text || !game->textures->grass_text
        || !game->textures->snow_text || !game->textures->stone_text
        || !game->textures->secret_text)
        return false;
    else
        return true;
}

static bool create_window(game_t *game)
{
    sfVideoMode mode = {GAME_WIDTH, GAME_HEIGHT, 32};

    game->window = sfRenderWindow_create(mode, "My_world", sfDefaultStyle,
        NULL);
    if (!game->window)
        return false;
    sfRenderWindow_setFramerateLimit(game->window, 60);
    return true;
}

static bool create_all(game_t *game)
{
    if (!create_window(game) || !create_background(game)
        || !create_start_btn(game) || !create_quit_btn(game)
        || !create_load_btn(game) || !create_raise_btn(game)
        || !create_lower_btn(game) || !create_flatten_btn(game)
        || !create_smooth_btn(game) || !create_menu_btn(game)
        || !create_save_btn(game) || !create_brush_ui(game)
        || !create_textures(game))
        return false;
    return true;
}

game_t *create_game(void)
{
    game_t *game = malloc(sizeof(game_t));

    if (!game)
        return NULL;
    if (!init_game(game)) {
        destroy_game(game);
        return NULL;
    }
    if (!create_all(game)) {
        destroy_game(game);
        return NULL;
    }
    return game;
}
