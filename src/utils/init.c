/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mysudo-39
** File description:
** init.c
*/

#include "../../include/my.h"

void init(data_t *data, int argc, char **argv)
{
    data->command = malloc(sizeof(char *) * argc);
    if (data->command != NULL) {
        for (int i = 0; i < argc; i++)
            data->command[i] = NULL;
    }
    data->flags = EMPTY;
    data->argc = argc;
    data->argv = argv;
    data->user_name = NULL;
    data->group_name = NULL;
    data->my_user_name = NULL;
    data->my_group_name = NULL;
    data->uid = 0;
    data->gid = 0;
    data->put_password = NULL;
    data->get_hashed_pass = NULL;
    data->good_pass = false;
    data->in_group = NULL;
    data->in_group_id = NULL;
}

void init_paser_struct(parser_t *s)
{
    s->array = NULL;
    s->double_array = NULL;
    s->buf = NULL;
    s->buf_idx = 0;
    s->str_len = 0;
}
