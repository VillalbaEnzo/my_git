/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mysudo-39
** File description:
** fill_in_group_id.c
*/

#include "../../include/my.h"

static void match_and_fill_id(data_t *data, char **group_line)
{
    for (int j = 0; data->in_group[j] != NULL; j++) {
        if (strcmp(group_line[0], data->in_group[j]) == 0) {
            free(data->in_group_id[j]);
            data->in_group_id[j] = strdup(group_line[2]);
        }
    }
}

void fill_in_group_id(data_t *data, parser_t *s)
{
    int how_many_group = 0;

    while (data->in_group[how_many_group] != NULL)
        how_many_group++;
    data->in_group_id = malloc(sizeof(char*) * (how_many_group + 1));
    for (int i = 0; i <= how_many_group; i++)
        data->in_group_id[i] = NULL;
    for (int i = 0; s->array[i] != NULL; i++)
        match_and_fill_id(data, s->array[i]);
}
