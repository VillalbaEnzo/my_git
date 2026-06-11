/*
** EPITECH PROJECT, 2025
** A-maze-d
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H
    #define INT_MAX 2147483647
    #define INT_MIN (-2147483648)

    #include <unistd.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <stdbool.h>
    #include <string.h>
    #include <ctype.h>
    #include <stdio.h>

typedef struct {
    int play_x;
    int play_y;
    char **grid;
    char p1;
    char p2;
    int size_grid;
    int curr_round;
} board_t;

/* SRC */
bool is_end(board_t *board);
void game_loop(board_t *board);
board_t *init_board(void);
bool parsing(board_t *board, char **args);
int free_and_return(board_t *board, int ret);
char **my_str_to_word_array(char const *str);
char *my_strncpy(char *dest, char const *src, int n);
void print_grid(board_t *board);
void fill_grid(board_t *board);
char **create_grid(board_t *board);
char **my_str_to_word_array(char const *str);

#endif
