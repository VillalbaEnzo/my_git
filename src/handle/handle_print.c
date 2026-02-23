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
        if (temp->type == 1) {
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
        if (temp->type == 2) {
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
        if (temp->type == 0)
            mini_printf("%i %i %i\n", temp->x, temp->y, temp->distance);
        temp = temp->next;
    }
}

void handle_print(all_t *all)
{
    mini_printf("#number_of_robots\n%i\n", all->maze->nb_robots);
    mini_printf("#rooms\n");
    print_start_room(all->room);
    print_end_room(all->room);
    print_classic_room(all->room);
    mini_printf("#tunnels\n");
}
