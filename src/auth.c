/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mysudo-39
** File description:
** auth.c
*/

#include "../include/my.h"

// https://aiins.cs.nthu.edu.tw/wp-content/uploads/2011/09/images
// _courses_CS5432_2016_18-termio.pdf

static void find_user_hashed_pass(data_t *data, parser_t *s)
{
    for (int i = 0; s->array[i] != NULL; i++) {
        if (strcmp(s->array[i][0], data->my_user_name) == 0) {
            data->get_hashed_pass = my_strdup(s->array[i][1]);
            break;
        }
    }
}

static bool get_user_password(data_t *data)
{
    parser_t *s = malloc(sizeof(parser_t));
    char *filepath = "/etc/shadow";
    int nbr_arg = 9;

    init_paser_struct(s);
    if (!load_file_and_fill_buf(s, filepath)) {
        free_struct_s(s);
        return false;
    }
    if (!file_parser(s, nbr_arg)) {
        free_struct_s(s);
        return false;
    }
    find_user_hashed_pass(data, s);
    free_struct_s(s);
    if (data->get_hashed_pass == NULL)
        return false;
    return true;
}

static bool check_user(parser_t *s, data_t *data, int i)
{
    int len_username = strlen(data->my_user_name);

    if (strncmp(s->double_array[i], data->my_user_name, len_username) == 0
        && (s->double_array[i][len_username] == ' '
            || s->double_array[i][len_username] == '\t'))
        return true;
    return false;
}

static bool check_group(parser_t *s, data_t *data, int i)
{
    char *line = s->double_array[i];
    int len;
    char next;

    if (line[0] != '%')
        return false;
    for (int k = 0; data->in_group[k] != NULL; k++) {
        len = strlen(data->in_group[k]);
        next = line[1 + len];
        if (strncmp(line + 1, data->in_group[k], len) == 0 &&
            (next == ' ' || next == '\t' || next == '\0' || next == '\n'))
            return true;
    }
    return false;
}

static bool check_group_id(parser_t *s, data_t *data, int i)
{
    char *line = s->double_array[i];
    int len = 0;
    char next;

    if (line[0] != '%' && line[1] != '#')
        return false;
    for (int k = 0; data->in_group_id[k] != NULL; k++) {
        len = strlen(data->in_group_id[k]);
        next = line[1 + len];
        if (strncmp(line + 2, data->in_group_id[k], len) == 0 &&
            (next == ' ' || next == '\t' || next == '\0' || next == '\n'))
            return true;
    }
    return false;
}

static bool check_user_id(parser_t *s, data_t *data, int i)
{
    char *line = s->double_array[i];
    char *temps;
    int len = 0;

    if (line[0] != '#')
        return false;
    while (line[1 + len] != '\0' && line[1 + len] != ' '
        && line[1 + len] != '\t')
        len++;
    temps = malloc(len + 1);
    if (!temps)
        return false;
    strncpy(temps, line + 1, len);
    temps[len] = '\0';
    if (atoi(temps) == data->my_uid) {
        free(temps);
        return true;
    }
    free(temps);
    return false;
}

static bool check_perm(data_t *data)
{
    parser_t *s = malloc(sizeof(parser_t));

    init_paser_struct(s);
    if (!load_file_and_fill_buf(s, "/etc/sudoers") || !fill_d_array(s)) {
        free_struct_s(s);
        return false;
    }
    for (int i = 0; s->double_array[i] != NULL; i++) {
        if (check_user(s, data, i) || check_user_id(s, data, i)) {
            free_struct_s(s);
            return true;
        }
        if (check_group(s, data, i) || check_group_id(s, data, i)) {
            free_struct_s(s);
            return true;
        }
    }
    fprintf(stderr, "%s is not in the my_sudoers file.\n", data->my_user_name);
    free_struct_s(s);
    return false;
}

bool auth(data_t *data)
{
    if (data->my_uid == 0)
        return true;
    if (!get_user_password(data))
        return false;
    read_and_cmp_psw_in_stdin(data);
    if (data->good_pass) {
        if (check_perm(data))
            return true;
    }
    return false;
}
