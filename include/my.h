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

/* STRUCT */
typedef struct node_s {
    struct node_s *next;
    struct node_s *end;
    char *line;
} node_t;

typedef struct room_s {
    struct room_s *next;
    char *name;
    int x;
    int y;
    int type;
    int visited;
    int distance;
    struct room_s *parent;
} room_t;

typedef struct neighbor_s {
    room_t *room;
    struct neighbor_s *next;
} neighbor_t;

typedef struct maze_s {
    int nb_robots;
    room_t *rooms;
    room_t *start;
    room_t *end;
} maze_t;

typedef struct all_s {
    room_t *room;
    maze_t *maze;
    neighbor_t *neighbor;
} all_t;

/* UTILS */
int my_strlen(char const *str);
int my_strcmp(char const *s1, char const *s2);
char *my_strncpy(char *dest, char const *src, int n);
char **load_input(void);

/* INIT */
int handle_init(all_t *all);
void init_maze(maze_t *maze);
void init_room(room_t *room);
void init_neighbor(neighbor_t *neighbor);

/* PARSING */
void parsing(char **buf, all_t *all);
int is_comment(char *line);

/* FREE */
void free_double_buf(char **buf);

/* CHAINED LIST */
node_t *create_node(char *line);
node_t *add_node(node_t *head, char *line);
node_t *del_node(node_t *head);

#endif
