/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mysudo-39
** File description:
** get_gid_from_file.c
*/

#include "../../include/my.h"

static bool is_user_in_list(char *list, char *user)
{
    int len = strlen(user);
    int i = 0;

    if (!list || !user)
        return false;
    while (list[i] != '\0') {
        if (strncmp(list + i, user, len) == 0 &&
            (list[i + len] == ',' || list[i + len] == '\0'))
            return true;
        while (list[i] != '\0' && list[i] != ',')
            i++;
        if (list[i] == ',')
            i++;
    }
    return false;
}

static bool should_add_group(data_t *data, char **line)
{
    if (!line[3])
        return false;
    if (!is_user_in_list(line[3], data->my_user_name))
        return false;
    if (data->my_group_name && strcmp(line[0], data->my_group_name) == 0)
        return false;
    return true;
}

static void fill_in_group(data_t *data, parser_t *s)
{
    int i = 0;
    int count = 0;

    while (s->array[i] != NULL)
        i++;
    data->in_group = malloc(sizeof(char *) * (i + 2));
    if (!data->in_group)
        return;
    if (data->my_group_name) {
        data->in_group[count] = my_strdup(data->my_group_name);
        count++;
    }
    for (i = 0; s->array[i]; i++) {
        if (should_add_group(data, s->array[i])) {
            data->in_group[count] = my_strdup(s->array[i][0]);
            count++;
        }
    }
    data->in_group[count] = NULL;
    fill_in_group_id(data, s);
}

static bool get_user_info_from_file(data_t *data)
{
    parser_t *s = malloc(sizeof(parser_t));
    char *filepath = "/etc/passwd";
    int nbr_arg = 7;

    init_paser_struct(s);
    if (!load_file_and_fill_buf(s, filepath) || !file_parser(s, nbr_arg)) {
        free_struct_s(s);
        return false;
    }
    find_my_user_name(data, s);
    if (data->flags == U_FLAG || data->flags == U_AND_G_FLAG) {
        find_user_id(data, s);
        find_group_id_flag_u(data, s);
        fill_in_group(data, s);
    }
    free_struct_s(s);
    if (data->uid == -1)
        return false;
    return true;
}

static bool get_group_info_from_file(data_t *data)
{
    parser_t *s = malloc(sizeof(parser_t));
    char *filepath = "/etc/group";
    int nbr_arg = 4;

    init_paser_struct(s);
    if (!load_file_and_fill_buf(s, filepath) || !file_parser(s, nbr_arg)) {
        free_struct_s(s);
        return false;
    }
    find_my_group_name(data, s);
    if (data->flags == G_FLAG || data->flags == U_AND_G_FLAG)
        find_group_id(data, s);
    fill_in_group(data, s);
    free_struct_s(s);
    return (data->gid != -1);
}

bool get_user_group_info(data_t *data)
{
    if (data->flags != H_FLAG)
        if (!get_user_info_from_file(data))
            return false;
    if (data->flags != H_FLAG)
        if (!get_group_info_from_file(data))
            return false;
    return true;
}
