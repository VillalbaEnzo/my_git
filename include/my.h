/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/types.h>
    #include <sys/wait.h>

typedef struct node_s {
    struct node_s *next;
    struct node_s *end;
    char *line;
} node_t;

/* CHAINED LIST */
node_t *create_node(char *line);
node_t *add_node(node_t *head, char *line);
node_t *del_node(node_t *head);
void free_list(node_t *head);

/* UTILS */
int my_putchar(char c);
int my_putstr(char const *str);
int my_putnbr(int nb);
int mini_printf(const char *format, ...);
void free_double_buf(char **buf);
int my_strcmp(char const *s1, char const *s2);
int my_strlen(char const *str);
char *my_strncpy(char *dest, char const *src, int n);
char *clear_line(char *str);

/* ENV */
int get_env(char **env, node_t *head);

/* SH */
int handle_sh(char *line, char **env);

#endif
