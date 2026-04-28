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
    STATE_PAUSE,
    STATE_COUNT
} game_state_t;

typedef enum {
    BTN_NEW_GAME,
    BTN_LOAD_GAME,
    BTN_SETTINGS,
    BTN_QUIT,
    BTN_COUNT
} menu_btn_t;

typedef enum {
    SFX_UI_SWITCH,
    SFX_UI_CLICK,
    SFX_UI_COUNT
} menu_sfx_t;

typedef enum {
    SET_MUSIC,
    SET_SFX,
    SET_RESIZE,
    SET_BACK,
    SET_COUNT
} settings_btn_t;

typedef struct audio_s {
    sfMusic *music;
    sfSound *sfx;
    sfSoundBuffer *buffer;
    float volume;
} audio_t;

typedef struct settings_s {
    sfRectangleShape *slider_bg[2];
    sfRectangleShape *slider_fill[2];
    sfSprite *bg_sprite;
    sfTexture *bg_texture;
    sfSprite *cursor_sprite;
    sfTexture *cursor_texture;
    int selected_btn;
    sfVector2f cursor_positions[SET_COUNT];
    sfText *btn_texts[SET_COUNT];
} settings_t;

typedef struct menu_s {
    sfSprite *bg_sprite;
    sfTexture *bg_texture;
    sfSprite *cursor_sprite;
    sfTexture *cursor_texture;
    int selected_btn;
    sfVector2f cursor_positions[BTN_COUNT];
    sfText *btn_texts[BTN_COUNT];
} menu_t;

typedef struct window_s {
    sfRenderWindow *render;
    sfEvent event;
    sfClock *clock;
    float dt;
    bool is_fullscreen;
} window_t;

typedef struct ui_s {
    audio_t *sfx[SFX_UI_COUNT];
    sfFont *font;
    audio_t *music;
    menu_t *menu;
    settings_t *settings;
} ui_t;

typedef struct map_s {
    int height;
    int witdh;
    int **grid;
} map_t;

typedef struct level_s {
    char *name;
    map_t *map;
    sfVector2f spawnpos;
    sfVector2f spawndir;
} level_t;

typedef struct player_s {
    sfVector2f pos;
    sfVector2f dir;
    sfVector2f plane;
    double move_speed;
    double rot_speed;
} player_t;

typedef struct ray_s {
    double cam_x;
    double dx;
    double dy;
    double delta_x;
    double delta_y;
    double side_x;
    double side_y;
    int map_x;
    int map_y;
    int step_x;
    int step_y;
    int hit;
    int side;
} ray_t;

typedef struct col_params_s {
    int x;
    int top;
    int bot;
    sfColor *color;
} col_params_t;

typedef struct game_s {
    game_state_t state;
    window_t *window;
    ui_t *ui;
    player_t *player;
    int active_level;
    level_t **levels;
    sfRectangleShape *render_half;
    sfRectangleShape *render_col;
} game_t;

#endif
