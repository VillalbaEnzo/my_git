/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** is_room.c
*/

#include "my.h"

int is_room(char *line)
{
    int i = 0;
    char **buf = my_str_to_word_array(line);

    if (!buf)
        return 0;
    while (buf[i])
        i++;
    if (i != 3) {
        free_double_buf(buf);
        return 0;
    }
    if (!is_nbr((buf[1])) || !is_nbr(buf[2])) {
        free(buf);
        return 0;
    }
    free_double_buf(buf);
    return 1;
}
