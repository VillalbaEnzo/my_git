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

void add_room(maze_t *maze, char *line, int type)
{
    room_t *new = init_room();
    char **tab = my_str_to_word_array(line);

    if (!new || !tab || !tab[0])
        return;
    new->name = my_strdup(tab[0]);
    new->x = my_getnbr(tab[1]);
    new->y = my_getnbr(tab[2]);
    new->type = type;
    append_room(maze, new);
    if (type == START) {
        maze->start = new;
        new->robot_count = maze->nb_robots;
    }
    if (type == END)
        maze->end = new;
    free_double_buf(tab);
}
