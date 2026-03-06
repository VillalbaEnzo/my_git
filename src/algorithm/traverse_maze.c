/*
** EPITECH PROJECT, 2026
** amazed [WSL: Ubuntu]
** File description:
** traverse_maze
*/

#include "my.h"

void move_robots(path_t *path, int i, int *robot_nbr)
{
    if (path->path[i + 1]->robot_count >= 1) {
        path->path[i]->robot_count++;
        path->path[i + 1]->robot_count--;
        (*robot_nbr)++;
        mini_printf("P%d-%s ", *robot_nbr, path->path[i]->name);
    }
}

void traverse_maze(maze_t *maze)
{
    path_t *path = bfs(maze);
    int robot_nbr = 0;

    while (path->path[0]->robot_count != maze->nb_robots) {
        robot_nbr = maze->end->robot_count;
        for (int i = 0; i < path->count - 1; i++) {
            move_robots(path, i, &robot_nbr);
        }
        mini_printf("\n");
    }
    free(path->path);
    free(path);
}
