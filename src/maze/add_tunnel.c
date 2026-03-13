/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** add_tunnel.c
*/

#include "my.h"

room_t *find_room(room_t *rooms, char *name)
{
    room_t *tmp = rooms;

    while (tmp) {
        if (my_strcmp(tmp->name, name) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

void link_rooms(room_t *r1, room_t *r2)
{
    neighbor_t *n1 = malloc(sizeof(neighbor_t));
    neighbor_t *n2 = malloc(sizeof(neighbor_t));

    if (!n1)
        return;
    if (!n2) {
        free(n1);
        return;
    }
    init_neighbor(n1);
    init_neighbor(n2);
    n1->room = r2;
    n1->next = r1->neighbors;
    r1->neighbors = n1;
    n2->room = r1;
    n2->next = r2->neighbors;
    r2->neighbors = n2;
}

void add_tunnel(maze_t *maze, char *line)
{
    int i = 0;
    room_t *r1 = NULL;
    room_t *r2 = NULL;

    while (line[i] != '\0' && line[i] != '-')
        i++;
    if (line[i] == '\0')
        return;
    line[i] = '\0';
    r1 = find_room(maze->rooms, line);
    r2 = find_room(maze->rooms, &line[i + 1]);
    if (r1 && r2)
        link_rooms(r1, r2);
    line[i] = '-';
}
