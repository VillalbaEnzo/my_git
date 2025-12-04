/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mysudo-39
** File description:
** free_prog.c
*/

#include "../../include/my.h"

static void free_user(data_t *data)
{
    if (data->user_name)
        free(data->user_name);
    if (data->my_user_name)
        free(data->my_user_name);
    if (data->command)
        free(data->command);
}

static void free_password(data_t *data)
{
    if (data->put_password)
        free(data->put_password);
    if (data->get_hashed_pass)
        free(data->get_hashed_pass);
}

static void free_group(data_t *data)
{
    if (data->group_name)
        free(data->group_name);
    if (data->my_group_name)
        free(data->my_group_name);
    if (data->in_group) {
        for (int i = 0; data->in_group[i] != NULL; i++)
            free(data->in_group[i]);
        free(data->in_group);
    }
    if (data->in_group_id) {
        for (int i = 0; data->in_group_id[i] != NULL; i++)
            free(data->in_group_id[i]);
        free(data->in_group_id);
    }
}

void free_prog(data_t *data)
{
    if (!data)
        return;
    free_user(data);
    free_password(data);
    free_group(data);
    free(data);
}
