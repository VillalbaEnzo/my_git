/*
** EPITECH PROJECT, 2025
** G-CPE-110-LYN-1-1-settingup-45
** File description:
** open_read.c
*/

#include "my.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

static char *read_virtual_file(const char *path)
{
    int fd;
    char *buf;
    int ret;

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return NULL;
    buf = malloc(sizeof(char) * (MAX_BUF_SIZE + 1));
    if (!buf)
        return close(fd), NULL;
    ret = read(fd, buf, MAX_BUF_SIZE);
    close(fd);
    if (ret == -1)
        return free(buf), NULL;
    buf[ret] = '\0';
    return buf;
}

static char *read_physical_file(const char *path)
{
    int fd;
    struct stat st;
    char *buf;

    if (stat(path, &st) == -1)
        return NULL;
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return NULL;
    buf = malloc((size_t)st.st_size + 1);
    if (!buf)
        return close(fd), NULL;
    read(fd, buf, (size_t)st.st_size);
    close(fd);
    buf[st.st_size] = '\0';
    return buf;
}

char **open_read(char *path, bool is_virtual)
{
    char *buf;
    char **arr;

    if (!path)
        return NULL;
    if (is_virtual)
        buf = read_virtual_file(path);
    else
        buf = read_physical_file(path);
    if (!buf)
        return NULL;
    arr = my_str_to_word_array(buf);
    free(buf);
    return arr;
}
