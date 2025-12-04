/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mysudo-39
** File description:
** file_parsing.c
*/

#include "../../include/my.h"

static int count_line(char *buf)
{
    int line = 0;

    for (int i = 0; buf[i] != '\0'; i++) {
        if (buf[i] == '\n')
            line++;
    }
    return line;
}

static void fill_str_array(parser_t *s, int i, int nbr_arg)
{
    s->array[i] = malloc(sizeof(char *) * (nbr_arg + 1));
    for (int j = 0; j < nbr_arg; j++) {
        s->str_len = 0;
        while (s->buf[s->buf_idx + s->str_len] != ':'
            && s->buf[s->buf_idx + s->str_len] != '\n'
            && s->buf[s->buf_idx + s->str_len] != '\0')
            s->str_len++;
        s->array[i][j] = malloc(sizeof(char) * (s->str_len + 1));
        strncpy(s->array[i][j], &s->buf[s->buf_idx], s->str_len);
        s->array[i][j][s->str_len] = '\0';
        s->buf_idx += s->str_len;
        if (s->buf[s->buf_idx] != '\0')
            s->buf_idx++;
    }
    s->array[i][nbr_arg] = NULL;
}

static void init_s(parser_t *s, char ***array)
{
    s->array = array;
    s->double_array = NULL;
    s->str_len = 0;
    s->buf_idx = 0;
}

bool file_parser(parser_t *s, int nbr_arg)
{
    int line = count_line(s->buf);
    char ***array;

    array = malloc(sizeof(char **) * (line + 1));
    if (array == NULL)
        return false;
    init_s(s, array);
    for (int i = 0; i < line; i++)
        fill_str_array(s, i, nbr_arg);
    array[line] = NULL;
    return true;
}
