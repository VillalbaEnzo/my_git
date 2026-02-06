/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** parsing.c
*/

#include "my.h"

void parsing(char **buf, all_t *all)
{
    for (int i = 0; buf[i]; i++) {
        printf("%s", buf[i]);
        if (is_comment(buf[i]) == 1)
            printf("is comment\n");
    }
}
