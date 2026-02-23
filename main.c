/*
** EPITECH PROJECT, 2025
** A-maze-d
** File description:
** main.c
*/

#include "../include/my.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char **buf;
    maze_t *maze = malloc(sizeof(maze_t));

    (void)argc;
    (void)argv;
    if (!maze)
        return 84;
    buf = load_input();
    if (!buf) {
        free(maze);
        return 84;
    }
    if (!handle_init(maze))
        return 84;
    parsing(buf, maze);
    handle_print(maze, buf);
    free_double_buf(buf);
    return 0;
}
