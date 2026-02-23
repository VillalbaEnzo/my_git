/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-amazed-1
** File description:
** handle_print.c
*/

#include "my.h"

static void print_start_room(room_t *room)
{
    room_t *temp = room;

    while (temp) {
        if (temp->type == START) {
            mini_printf("##start\n%i %i %i\n", temp->x, temp->y,
                temp->distance);
            break;
        }
        temp = temp->next;
    }
}

static void print_end_room(room_t *room)
{
    room_t *temp = room;

    while (temp) {
        if (temp->type == END) {
            mini_printf("##end\n%i %i %i\n", temp->x, temp->y, temp->distance);
            break;
        }
        temp = temp->next;
    }
}

static void print_classic_room(room_t *room)
{
    room_t *temp = room;

    while (temp) {
        if (temp->type == NORMAL)
            mini_printf("%i %i %i\n", temp->x, temp->y, temp->distance);
        temp = temp->next;
    }
}

void handle_print(maze_t *maze, char **buf)
{
    mini_printf("#number_of_robots\n%i\n", maze->nb_robots);
    mini_printf("#rooms\n");
    print_start_room(maze->rooms);
    print_end_room(maze->rooms);
    print_classic_room(maze->rooms);
    mini_printf("#tunnels\n");
    for (int i = 0; buf[i]; i++) {
        if (is_tunnel(buf[i]))
            mini_printf("%s\n", buf[i]);
    }
    mini_printf("#moves\n");
}
