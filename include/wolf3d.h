/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5
** File description:
** wolf3d.h
*/

#ifndef WOLF3D_H
    #define WOLF3D_H
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <math.h>

    #include "wolf/macros.h"
    #include "wolf/structs.h"
    #include "wolf/assets.h"

/* INIT */
game_t *init_game(void);
window_t *init_window(void);
ui_t *init_ui(void);
audio_t *init_audio(char *audio_path, bool music);
menu_t *init_menu(sfFont *font);
settings_t *init_setting(sfFont *font);
level_t **init_levels(void);
player_t *init_player(void);

/* GAME */
void game_loop(game_t *game);
void display_page(game_t *game);

/* RENDER */
void render(game_t *game, map_t *map);

/* EVENT */
void handle_events(game_t *game);
void handle_movement(game_t *game, sfEvent event);
void handle_menu_events(game_t *game, sfEvent event);
void handle_settings_events(game_t *game, sfEvent event);

/* FREE */
void free_game(game_t *game);
void free_audio(audio_t *audio);
void free_ui(game_t *game);
void free_window(game_t *game);
void free_level(level_t *level);
void free_levels(level_t **levels);

#endif
