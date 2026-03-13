/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** init_neighbor.c
*/

#include "my.h"

void init_neighbor(neighbor_t *neighbor)
{
    neighbor->next = NULL;
    neighbor->room = NULL;
}
