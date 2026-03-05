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
    #define FONT_PATH "assets/font/DelaGothicOne.ttf"
    #define BG_PATH "assets/images/background.png"
    #define START_BTN "assets/images/start_btn.png"
    #define LOAD_BTN "assets/images/load_btn.png"
    #define QUIT_BTN "assets/images/quit_btn.png"

typedef enum game_state_e {
    START_MENU,
    PLAYING,
    LOADMAP
} game_state_t;

typedef struct map_s {
    int width;
    int height;
    float **z_map;
    sfVector2f **points_2d;
    sfVertexArray *terrain;
    float angle_x;
    float angle_y;
    float zoom;
    sfVector2f offset;
    float rotation;
} map_t;

typedef enum ui_state_e {
    SAVE,
    MENU,
    RAISE,
    LOWER,
    FLATTEN,
    SMOOTH,
    INPUT_RADIUS,
    INPUT_STRENGTH
} ui_state_t;

typedef struct brush_s {
    sfText *radius_label;
    sfRectangleShape *radius_box;
    sfText *radius_text;
    char *radius_input;
    int radius_pos;
    sfText *strength_label;
    sfRectangleShape *strength_box;
    sfText *strength_text;
    char *strength_input;
    int strength_pos;
} brush_t;

typedef struct button_s {
    sfRectangleShape *rect;
    sfTexture *texture;
    sfText *help_text;
} button_t;

typedef struct background_s {
    sfSprite *bg_sp;
    sfTexture *bg_tx;
} bg_t;

typedef struct tools_bar_s {
    sfText *raise_btn;
    sfText *lower_btn;
    sfText *flatten_btn;
    sfText *smooth_btn;
    brush_t *brush;
} tools_bar_t;

typedef struct playing_ui_s {
    tools_bar_t *tb;
    sfText *menu_btn;
    sfText *save_btn;
    sfRectangleShape *input_box;
    sfText *save_input;
    char *input;
    int input_pos;
    ui_state_t ui_state;
} playing_ui_t;

typedef struct menu_s {
    button_t *start_btn;
    button_t *load_btn;
    button_t *quit_btn;
} menu_t;

typedef struct game_s {
    sfFont *font;
    map_t *map;
    playing_ui_t *pl_ui;
    sfRenderWindow *window;
    sfEvent event;
    sfClock *clock;
    bg_t *bg;
    float dt;
    bool is_running;
    sfMusic *music;
    game_state_t state;
    menu_t *start_menu;
    bool mouse_clicked;
} game_t;

//INIT
bool init_game(game_t *game);

//START MENU
void start_menu_display(game_t *game);
void load_display(game_t *game);
void playing_display(game_t *game);
void update_menu_btn(game_t *game);

//CREATE
game_t *create_game(void);
bool create_start_btn(game_t *game);
bool create_quit_btn(game_t *game);
bool create_load_btn(game_t *game);
bool create_background(game_t *game);
bool create_raise_btn(game_t *game);
bool create_smooth_btn(game_t *game);
bool create_flatten_btn(game_t *game);
bool create_lower_btn(game_t *game);
bool create_save_btn(game_t *game);
bool create_menu_btn(game_t *game);
bool create_brush_ui(game_t *game);

//HANDLE MENU BTN
void handle_quit_btn(game_t *game);
void handle_load_btn(game_t *game);
void handle_start_btn(game_t *game);

//PLAYING
void update_tools_bar_btn(game_t *game);
void update_other_btn(game_t *game);
void update_playing_btn(game_t *game);

//HANDLE PLAYING OTHER BTN
void handle_menu_btn(game_t *game);

//HANDLE TOOLS BAR BTN
void handle_lower_btn(game_t *game);
void handle_raise_btn(game_t *game);
void handle_smooth_btn(game_t *game);
void handle_flatten_btn(game_t *game);
void handle_save_btn(game_t *game);
//BRUSH
void apply_brush(game_t *game, int target_x, int target_y);
void flatten_brush(game_t *game, int center_x, int center_y);
void lower_brush(game_t *game, int center_x, int center_y);
void raise_brush(game_t *game, int center_x, int center_y);
void smooth_brush(game_t *game, int center_x, int center_y);
void handle_brush_click(game_t *game);

//INPUT
void display_user_input(game_t *game);
void display_brush_ui(game_t *game);

//GAME
void game_loop(game_t *game);
void destroy_game(game_t *game);
void manage_events(game_t *game);

//MAP
void update_2d_map(game_t *game);
void draw_map(game_t *game);
bool init_map(game_t *game);
void handle_map_events(game_t *game, sfEvent event);
void handle_map_click(game_t *game);

#endif
