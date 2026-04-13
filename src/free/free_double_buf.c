/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** list_free.c
*/

#include "my.h"

void free_double_buf(char **buf)
{
    for (int i = 0; buf[i]; i++)
        free(buf[i]);
    free(buf);
}
