/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mysudo-39
** File description:
** free_struct_s.c
*/

#include "../../include/my.h"

static void free_chara(parser_t *s, int i)
{
    for (int j = 0; s->array[i][j] != NULL; j++)
        free(s->array[i][j]);
}

void free_struct_s(parser_t *s)
{
    if (s->array) {
        for (int i = 0; s->array[i] != NULL; i++) {
            free_chara(s, i);
            free(s->array[i]);
        }
        free(s->array);
    }
    if (s->double_array) {
        for (int i = 0; s->double_array[i] != NULL; i++)
            free(s->double_array[i]);
        free(s->double_array);
    }
    if (s->buf)
        free(s->buf);
    free(s);
}
