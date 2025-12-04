/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mysudo-39 [WSL: Ubuntu-24.04]
** File description:
** find.c
*/

#include "../../include/my.h"

void find_user_id(data_t *data, parser_t *s)
{
    for (int i = 0; s->array[i] != NULL; i++) {
        if (strcmp(s->array[i][0], data->user_name) == 0) {
            data->uid = atoi(s->array[i][2]);
            break;
        } else
            data->uid = -1;
    }
}

void find_group_id(data_t *data, parser_t *s)
{
    data->gid = -1;
    for (int i = 0; s->array[i] != NULL; i++) {
        if (strcmp(s->array[i][0], data->group_name) == 0) {
            data->gid = atoi(s->array[i][2]);
            break;
        }
    }
}

void find_group_id_flag_u(data_t *data, parser_t *s)
{
    data->gid = -1;
    for (int i = 0; s->array[i] != NULL; i++) {
        if (strcmp(s->array[i][0], data->user_name) == 0) {
            data->gid = atoi(s->array[i][3]);
            break;
        }
    }
}

void find_my_user_name(data_t *data, parser_t *s)
{
    for (int i = 0; s->array[i] != NULL; i++) {
        if (atoi(s->array[i][2]) == data->my_uid) {
            data->my_user_name = my_strdup(s->array[i][0]);
            break;
        }
    }
}

void find_my_group_name(data_t *data, parser_t *s)
{
    for (int i = 0; s->array[i] != NULL; i++) {
        if (atoi(s->array[i][2]) == data->my_gid) {
            data->my_group_name = my_strdup(s->array[i][0]);
            break;
        }
    }
}
