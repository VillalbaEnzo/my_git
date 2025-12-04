/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mysudo-39
** File description:
** main.c
*/

#include "../include/my.h"

static bool handle_parser(data_t *data)
{
    if (!parser(data)) {
        free_prog(data);
        return false;
    }
    return true;
}

static bool handle_password(data_t *data)
{
    if (!data->good_pass) {
        free_prog(data);
        return false;
    }
    return true;
}

static bool handle_execute(data_t *data)
{
    if (!execute(data)) {
        free_prog(data);
        return false;
    }
    return true;
}

int main(int argc, char **argv)
{
    data_t *data = malloc(sizeof(data_t));

    if (!data)
        return 84;
    init(data, argc, argv);
    if (!handle_parser(data))
        return 84;
    if (data->flags == H_FLAG) {
        free_prog(data);
        return 0;
    }
    if (!auth(data))
        return 84;
    if (data->my_uid != 0 && !handle_password(data))
        return 84;
    if (!handle_execute(data))
        return 84;
    free_prog(data);
    return 0;
}
