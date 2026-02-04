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
    char **buf = open_read();

    for (int i = 0; buf[i]; i++)
        printf("%s", buf[i]);
    for (int i = 0; buf[i]; i++)
        free(buf[i]);
    free(buf);
    return 0;
}
