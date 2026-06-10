/*
** EPITECH PROJECT, 2025
** pokemon [WSL: Ubuntu-24.04]
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <dirent.h>
    #include <stdbool.h>
    #include <time.h>
    #include <ctype.h>

typedef struct pokemon_s {
    char *name;
    int attack;
    int defense;
    int speed;
    int heal;
    struct pokemon_s *next;
} pokemon_t;

/* FUNC */
bool parse_folder(char *folder_path, pokemon_t **head);
bool game_loop(pokemon_t *one, pokemon_t *two);

/* CHAINED LIST */
pokemon_t *create_node(pokemon_t *head, char **arg);
void free_pokemons(pokemon_t *head);
pokemon_t *sort_pokemon(pokemon_t *head);
pokemon_t *init_pokemon(char **arg);
void print_pokemon_info(pokemon_t *head);
pokemon_t *get_node_by_name(pokemon_t *head, char *name);

/* UTILS */
char **str_to_word_array(char *str, char *delims);
void free_double_array(char **array);

#endif
