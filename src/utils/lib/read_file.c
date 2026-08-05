/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** read_file.c
*/

#include "my.h"

static void *free_ret(void *to_free)
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
