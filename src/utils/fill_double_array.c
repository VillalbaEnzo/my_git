/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mysudo-39
** File description:
** buffer_to_line.c
*/

#include "../../include/my.h"

static int count_line(char *buf)
{
    int count = 0;

    if (buf == NULL)
        return 0;
    for (int i = 0; buf[i] != '\0'; i++) {
        if (buf[i] == '\n')
            count++;
    }
    if (buf[0] != '\0' && buf[strlen(buf) - 1] != '\n')
        count++;
    return count;
}

static char *extract_one_line(char *buf, int *i)
{
    int len = 0;
    char *str;

    while (buf[*i + len] != '\0' && buf[*i + len] != '\n')
        len++;
    str = malloc(sizeof(char) * (len + 1));
    if (str == NULL)
        return NULL;
    strncpy(str, &buf[*i], len);
    str[len] = '\0';
    *i += len;
    if (buf[*i] == '\n')
        (*i)++;
    return str;
}

bool fill_d_array(parser_t *s)
{
    int lines;
    int i = 0;
    int j = 0;

    if (s == NULL || s->buf == NULL)
        return false;
    lines = count_line(s->buf);
    s->double_array = malloc(sizeof(char *) * (lines + 1));
    if (s->double_array == NULL)
        return false;
    while (s->buf[i] != '\0') {
        s->double_array[j] = extract_one_line(s->buf, &i);
        if (s->double_array[j] == NULL)
            return false;
        j++;
    }
    s->double_array[j] = NULL;
    return true;
}
