/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mysudo-39
** File description:
** parser.c
*/

#include "../include/my.h"

static void u_flag(data_t *data, int i)
{
    if (data->command == NULL)
        return;
    if (strcmp(data->argv[1], "-u") == 0
        && data->flags != U_AND_G_FLAG && data->flags != H_FLAG && i != 1) {
        data->command[i - 3] = data->argv[i];
        if (data->user_name == NULL)
            data->user_name = my_strdup(data->argv[2]);
        data->command[data->argc - 3] = NULL;
        data->flags = U_FLAG;
    }
}

static void g_flag(data_t *data, int i)
{
    if (data->command == NULL)
        return;
    if (strcmp(data->argv[1], "-g") == 0
        && data->flags != U_AND_G_FLAG && data->flags != H_FLAG && i != 1) {
        data->command[i - 3] = data->argv[i];
        if (data->group_name == NULL)
            data->group_name = my_strdup(data->argv[2]);
        data->command[data->argc - 3] = NULL;
        data->flags = G_FLAG;
    }
}

static void u_and_g_flag(data_t *data, int i)
{
    if ((strcmp(data->argv[1], "-u") == 0 && strcmp(data->argv[3], "-g") == 0)
        && i != 1) {
        data->command[i - 5] = data->argv[i];
        if (data->user_name == NULL)
            data->user_name = my_strdup(data->argv[2]);
        if (data->group_name == NULL)
            data->group_name = my_strdup(data->argv[4]);
        data->command[data->argc - 5] = NULL;
        data->flags = U_AND_G_FLAG;
    }
    if ((strcmp(data->argv[1], "-g") == 0 && strcmp(data->argv[3], "-u") == 0)
        && i != 1) {
        data->command[i - 5] = data->argv[i];
        if (data->user_name == NULL)
            data->user_name = my_strdup(data->argv[4]);
        if (data->group_name == NULL)
            data->group_name = my_strdup(data->argv[2]);
        data->command[data->argc - 5] = NULL;
        data->flags = U_AND_G_FLAG;
    }
}

static void empty_flag(data_t *data, int i)
{
    if (data->flags == EMPTY) {
        data->command[i - 1] = data->argv[i];
        data->command[data->argc - 1] = NULL;
    }
}

static void h_flag(data_t *data)
{
    if (data->argc >= 2 && strcmp(data->argv[1], "-h") == 0) {
        printf("usage: ./my_sudo -h\n");
        printf("usage: ./my_sudo [-ug] [command [args ...]]\n");
        data->flags = H_FLAG;
    }
}

static void flags(data_t *data)
{
    int i = 1;

    if (strcmp(data->argv[1], "-u") == 0 || strcmp(data->argv[1], "-g") == 0)
        i = 3;
    if (data->argc >= 5 && ((strcmp(data->argv[1], "-u") == 0
                && strcmp(data->argv[3], "-g") == 0)
            || (strcmp(data->argv[1], "-g") == 0
                && strcmp(data->argv[3], "-u") == 0)))
        i = 5;
    while (i < data->argc) {
        if (data->flags == H_FLAG)
            break;
        h_flag(data);
        u_and_g_flag(data, i);
        u_flag(data, i);
        g_flag(data, i);
        empty_flag(data, i);
        i++;
    }
}

static bool check_error(data_t *data)
{
    if (data->command == NULL || data->command[0] == NULL)
        return false;
    if (data->uid == -1)
        return false;
    if (data->gid == -1)
        return false;
    return true;
}

// static void print_test(data_t *data)
// {
//     printf("uid: %i\n", data->uid);
//     printf("gid: %i\n", data->gid);
//     printf("my_uid: %u\n", data->my_uid);
//     printf("my_gid: %u\n", data->my_gid);
//     if (data->command)
//         printf("command: %s\n", data->command[0]);
//     for (int i = 1; data->command[i] != NULL; i++)
//         printf("option%i: %s\n", i, data->command[i]);
//     printf("user: %s\n", data->user_name);
//     printf("grp: %s\n", data->group_name);
//     printf("my_user: %s\n", data->my_user_name);
//     printf("my_grp: %s\n", data->my_group_name);
//     for (int i = 0; data->in_group[i]; i++)
//         printf("in group: %s\n", data->in_group[i]);
//     for (int i = 0; data->in_group_id[i]; i++)
//         printf("in group id: %s\n", data->in_group_id[i]);
// }
bool parser(data_t *data)
{
    if (data->argc <= 1) {
        fprintf(stderr, "usage: ./my_sudo -h\n");
        fprintf(stderr, "usage: ./my_sudo [-ug] [command [args ...]]\n");
        return false;
    }
    flags(data);
    if (data->flags == H_FLAG)
        return true;
    data->my_uid = getuid();
    data->my_gid = getgid();
    get_user_group_info(data);
    if (!check_error(data))
        return false;
    return true;
}
    // if (data->flags != H_FLAG)
    //     print_test(data);
