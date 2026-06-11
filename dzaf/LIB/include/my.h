/*
** EPITECH PROJECT, 2025
** LIB
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <unistd.h>

typedef struct {
    char **array;
    int width;
    int height;
} array_t;

typedef struct {
    int x;
    int y;
} coord_t;

/* ARRAY */
array_t *create_array(int width, int height);
void free_array(array_t *array);
void fill_array(array_t *array, char c);
array_t *copy_array(array_t *array);
bool set_char(array_t *array, coord_t *coord, char c);
char get_char(array_t *array, coord_t *coord);
bool move_element(array_t *array, coord_t *pos, coord_t *dir, char empty_char);
void print_array(array_t *array);
bool swap_element(array_t *array, coord_t *src, coord_t *dest);

/* PARSING */
void free_double_array(char **array);
char **str_to_word_array(char *str, char *delims);
char **get_file(char *filepath);

#endif
