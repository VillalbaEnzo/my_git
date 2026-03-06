/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** init_room.c
*/

#include "my.h"

room_t *init_room(void)
{
    room_t *temp = malloc(sizeof(room_t));

    temp->distance = 0;
    temp->next = NULL;
    temp->name = NULL;
    temp->parent = NULL;
    temp->type = 0;
    temp->visited = 0;
    temp->x = 0;
    temp->y = 0;
    temp->robot_count = 0;
    temp->neighbors = NULL;
    return temp;
}
