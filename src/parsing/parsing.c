/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** parsing.c
*/

#include "my.h"

void parsing(char **buf, all_t *all)
{
    int type = 0;

    for (int i = 0; buf[i]; i++) {
        if (is_command(buf[i], &type))
            continue;
        if (is_tunnel(buf[i])) {
            //add_tunnel(all);
            // continue;
        }
        if (is_room(buf[i])) {
            //add_room(all);
            type = 0;
            // continue;
        }
        if (all->maze->nb_robots == 0)
            all->maze->nb_robots = my_getnbr(buf[i]);
        printf("%s\n", buf[i]);
    }
    printf("robot : %i\n", all->maze->nb_robots);
}
