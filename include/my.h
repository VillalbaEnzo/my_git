/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** my.h
*/

#ifndef MY_WORLD_H_
    #define MY_WORLD_H_
    #include <SFML/Audio.h>
    #include <SFML/Graphics.h>
    #include <math.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <string.h>
    #define GAME_WIDTH 1920
    #define GAME_HEIGHT 1080
    #define GAME_WIDTH2 800
    #define GAME_HEIGHT2 600
    #define TILE_SIZE 64
    #define BG_PATH "assets/images/background.png"

typedef struct map_s {
    int width;
    int height;
    float **z_map;
    sfVector2f **points_2d;
    sfVertexArray *terrain;
    float angle_x;
    float angle_y;
    float zoom;
} map_t;

typedef enum button_state_e {
    IDLE,
    HOVER,
    CLICKED
} button_state_t;

typedef struct button_s {
    sfRectangleShape *rect;
    sfTexture *texture;
    button_state_t state;
    void (*function)(void *);
    sfText *help_text;
} button_t;

typedef struct background_s {
    sfSprite *bg_sp;
    sfTexture *bg_tx;
} bg_t;

typedef struct game_s {
    sfRenderWindow *window;
    sfEvent event;
    sfClock *clock;
    bg_t *bg;
    float dt;
    bool is_running;
    sfMusic *music;
} game_t;

void init_game(game_t *game);
bool create_background(game_t *game);
game_t *create_game(void);
void game_loop(game_t *game);
void init_game(game_t *game);
void manage_events(game_t *game);
void destroy_game(game_t *game);

#endif
