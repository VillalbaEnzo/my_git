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

/* INIT */

game_t *init_game(void);
window_t *init_window(void);
menu_t *init_menu(void);

/* GAME */

void game_loop(game_t *game);
void display_page(game_t *game);

/* EVENT */

void handle_events(game_t *game);
void handle_menu_events(game_t *game, sfEvent event);

/* FREE */

void free_game(game_t *game);

#endif
