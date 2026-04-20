/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** structs.h
*/

#ifndef STRUCTS_H
    #define STRUCTS_H

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <stdbool.h>

typedef enum {
    STATE_MENU,
    STATE_SETTINGS,
    STATE_PLAY,
    STATE_PAUSE
} game_state_t;

typedef struct window_s {
    sfRenderWindow *render;
    sfEvent event;
    sfClock *clock;
    float dt;
    bool is_fullscreen;
} window_t;

typedef struct audio_s {
    sfMusic *bg_music;
    float volume;
} audio_t;

typedef struct ui_s {
} ui_t;

typedef struct game_s {
    game_state_t state;
    window_t *window;
    audio_t *audio;
    ui_t *ui;
} game_t;

#endif
