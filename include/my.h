/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H
    #define HOME_PATH "/home/enzovillalba" // a faire!!!
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/types.h>
    #include <sys/wait.h>

/* CHAINED LIST */
typedef struct node_s {
    struct node_s *next;
    struct node_s *end;
    char *line;
} node_t;

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
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strcpy(char *dest, char const *src);
int my_strlen(char const *str);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strdup(char const *src);
char **str_to_tab(char *str);
char *my_strcat(char *dest, char const *src);

/* ENV */
int get_env(char **env, node_t **head);
char *get_path(node_t *head, char *cmd);
char *find_in_path(char *path, char *cmd);

/* HANDLE */
void handle_sh(node_t *head, char **env);
void handle_path(node_t *head, char **cmd);
int handle_fork(char **cmd, node_t *head);
void handle_buildins(char **cmd, int build, node_t **head);

/* BUILDINS */
void print_env(char **cmd, node_t *head);
node_t *set_env(char **cmd, node_t *head);
node_t *unset_env(char **cmd, node_t *head);
void my_cd(char **cmd, node_t *head);

/* FREE */
void free_double_buf(char **buf);

#endif
