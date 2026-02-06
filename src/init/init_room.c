/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** init_room.c
*/

#include "my.h"

void init_room(room_t *room)
{
    room->distance = 0;
    room->next = NULL;
    room->name = NULL;
    room->parent = NULL;
    room->type = 0;
    room->visited = 0;
    room->x = 0;
    room->y = 0;
}
