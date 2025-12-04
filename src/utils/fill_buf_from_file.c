/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mysudo-39
** File description:
** fill_buf_from_file.c
*/

#include "../../include/my.h"

static bool fill_buffer_from_file(char *filepath, char *buf, int size)
{
    int fd = open(filepath, O_RDONLY);

    if (fd == -1)
        return false;
    if (read(fd, buf, size) == -1) {
        close(fd);
        return false;
    }
    close(fd);
    return true;
}

bool load_file_and_fill_buf(parser_t *s, char *filepath)
{
    struct stat file_stats;

    if (stat(filepath, &file_stats) == -1)
        return false;
    s->buf = malloc(sizeof(char) * (file_stats.st_size + 1));
    if (s->buf == NULL)
        return false;
    if (!fill_buffer_from_file(filepath, s->buf, file_stats.st_size)) {
        free(s->buf);
        s->buf = NULL;
        return false;
    }
    s->buf[file_stats.st_size] = '\0';
    return true;
}
