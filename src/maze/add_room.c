/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** add_room.c
*/

#include "my.h"

void add_room(maze_t *maze, char *line, int type)
{
    room_t *new = malloc(sizeof(room_t));
    char **tab = my_str_to_word_array(line);

    if (!new || !tab || !tab[0])
        return;
    init_room(new);
    new->name = my_strdup(tab[0]);
    new->x = my_getnbr(tab[1]);
    new->y = my_getnbr(tab[2]);
    new->type = type;
    new->next = maze->rooms;
    maze->rooms = new;
    if (type == START)
        maze->start = new;
    if (type == END)
        maze->end = new;
    free_double_buf(tab);
}
