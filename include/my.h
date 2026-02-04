/*
** EPITECH PROJECT, 2025
** A-maze-d
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H
    #include <stdio.h>
    #include <stdlib.h>

int my_strlen(char const *str);
int my_strcmp(char const *s1, char const *s2);
char **open_read(void);
char *my_strdup(char const *src);

typedef struct node_s {
    struct node_s *next;
    char *line;
} node_t;

node_t *create_node(char *line);
node_t *add_node(node_t *head, char *line);
node_t *del_node(node_t *head);

#endif
