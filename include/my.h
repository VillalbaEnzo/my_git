/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31 [WSL: Ubuntu-24.04]
** File description:
** my.h
*/
#ifndef MY_H_
    #define MY_H_
    #include <SFML/Audio.h>
    #include <SFML/Graphics.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <time.h>
    #include <string.h>
    #include <unistd.h>
    #include <stdarg.h>
    #define _GNU_SOURCE
    #define GAME_WIDTH 1920
    #define GAME_HEIGHT 1080
    #define INT_MAX 2147483647
    #define INT_MIN (-2147483648)

typedef enum game_state_e
{
    START_MENU,
    PLAYING,
    PAUSED,
    LOOSE
} game_state_t;

typedef struct sprite_list_s {
    bool is_plane;
    sfVector2f start_pos;
    sfVector2f end_pos;
    sfVector2f current_pos;
    float speed;
    int delay;
    bool has_taken_off;
    bool has_arrived;

    int radius;

    sfSprite *sprite;
    sfTexture *texture;
    sfRectangleShape *hitbox;
    sfCircleShape *area;
    struct sprite_list_s *next;
} sprite_list_t;

typedef struct game_s
{
    game_state_t state;
    sfRenderWindow *window;
    sfSprite *background_sprite;
    sfTexture *background_texture;
    sprite_list_t *entities;
} game_t;

game_t *create_game(void);
void destroy_game(game_t *game);
void game_loop(game_t *game);
void manage_events(game_t *game);
void init(game_t *game);

bool create_background(game_t *game);

int my_strcmp(char const *s1, char const *s2);
int my_putstr(char const *str);
int my_putchar(char c);
int my_put_nbr(int nb);
int mini_printf(const char *format, ...);
char *unsigned_int_to_str(unsigned int n);
char *my_revstr(char *str);
int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);
char **my_str_to_word_array(char const *str);
void free_array(char **arr);
int my_getnbr(char const *str);

bool get_start_coord(game_t *game, const char *filepath);
void init_sprite_list(sprite_list_t *sprite_list);

#endif
