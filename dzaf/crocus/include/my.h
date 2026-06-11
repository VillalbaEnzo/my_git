/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my.h
*/

#ifndef MY
    #define MY
    #include <unistd.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <ctype.h>
    #include <stdarg.h>

/* STRUCT */
typedef struct {
    char line[5][6];
} number_t;

typedef struct {
    char *flag_s;
    char *flag_n;
    bool has_s;
} parsing_t;


extern const number_t number[];

/* FUNC */
void print_nbr(char *nbr, char *letter);
bool handle_error(int argc, parsing_t *pars);
char *create_string(parsing_t *pars);
int free_ret(char *str, parsing_t *pars, int ret);
void handle_parsing(char **argv, parsing_t *pars);
parsing_t *init_parsing(void);

#endif
