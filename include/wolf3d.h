/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** wolf3d.h
*/

#ifndef WOLF3D_H
    #define WOLF3D_H
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <unistd.h>
    #include "structs.h"
    #define BG_MUSIC_PATH "./assets/sounds/music/bg_music.ogg"

/* INIT */

game_t *init_game(void);
window_t *init_window(void);
audio_t *init_audio(void);
menu_t *init_menu(void);

/* MENU */

void execute_menu_action(game_t *game);
void handle_menu(game_t *game);

/* GAME */

void game_loop(game_t *game);
void display_menu(game_t *game);

/* EVENT */

void handle_events(game_t *game);

/* FREE */

void free_game(game_t *game);

#endif
