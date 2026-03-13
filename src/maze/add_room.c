/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** add_room.c
*/

#include "my.h"

static void append_room(maze_t *maze, room_t *new)
{
    room_t *tmp = maze->rooms;

    if (!maze->rooms) {
        maze->rooms = new;
        return;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
}

static int is_room_valid(maze_t *maze, char **tab, int type)
{
    room_t *tmp = maze->rooms;

    if (!tab || !tab[0] || !tab[1] || !tab[2])
        return 0;
    while (tmp) {
        if (my_strcmp(tmp->name, tab[0]) == 0)
            return 0;
        if (tmp->x == my_getnbr(tab[1]) && tmp->y == my_getnbr(tab[2]))
            return 0;
        tmp = tmp->next;
    }
    if (type == START && maze->start != NULL)
        return 0;
    if (type == END && maze->end != NULL)
        return 0;
    return 1;
}

static void set_special_room(maze_t *maze, room_t *new, int type)
{
    if (type == START) {
        maze->start = new;
        new->robot_count = maze->nb_robots;
    }
    if (type == END)
        maze->end = new;
}

int add_room(maze_t *maze, char *line, int type)
{
    room_t *new = NULL;
    char **tab = my_str_to_word_array(line);

    if (!is_room_valid(maze, tab, type))
        return 0;
    new = init_room();
    if (!new)
        return 0;
    new->name = my_strdup(tab[0]);
    new->x = my_getnbr(tab[1]);
    new->y = my_getnbr(tab[2]);
    new->type = type;
    append_room(maze, new);
    set_special_room(maze, new, type);
    free_double_buf(tab);
    return 1;
}
