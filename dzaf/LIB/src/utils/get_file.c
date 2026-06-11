/*
** EPITECH PROJECT, 2025
** LIB [WSL: Ubuntu-24.04]
** File description:
** get_file.c
*/

#include "my.h"

void *free_ret(void *to_free)
{
    free(to_free);
    return NULL;
}

char *read_file(int fd)
{
    char *str = NULL;
    struct stat stats;
    ssize_t r;
    ssize_t total = 0;

    if (fstat(fd, &stats) == -1)
        return NULL;
    if (stats.st_size == 0)
        return NULL;
    str = malloc(sizeof(char) * (stats.st_size + 1));
    if (!str)
        return NULL;
    while (total < stats.st_size) {
        r = read(fd, str + total, stats.st_size - total);
        if (r <= 0)
            return free_ret(str);
        total += r;
    }
    str[total] = '\0';
    return str;
}

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
