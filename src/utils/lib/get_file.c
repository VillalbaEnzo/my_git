/*
** EPITECH PROJECT, 2025
** LIB [WSL: Ubuntu-24.04]
** File description:
** get_file.c
*/

#include "my.h"

char **get_file(char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    char **ret = NULL;
    char *str = NULL;

    if (fd == -1)
        return NULL;
    str = read_file(fd);
    if (!str) {
        close(fd);
        return NULL;
    }
    ret = str_to_word_array(str, "\n");
    free(str);
    close(fd);
    if (!ret)
        return NULL;
    return ret;
}
