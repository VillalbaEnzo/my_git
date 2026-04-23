/*
** EPITECH PROJECT, 2026
** duo_stumper_5
** File description:
** open_read
*/

#include "my.h"

long get_file_size(const char *filename)
{
    struct stat st;

    if (stat(filename, &st) != 0)
        return -1;
    return st.st_size;
}

int open_file(const char *filename)
{
    int f = open(filename, O_RDONLY);

    if (f < 0)
        return -1;
    return f;
}

char *read_file(const char *filename)
{
    long size = get_file_size(filename);
    char *buffer = malloc(sizeof(char) * (size + 1));
    int f = open_file(filename);

    if (!buffer) {
        close(f);
        return NULL;
    }
    if (!f || size < 0)
        return NULL;
    if (read(f, buffer, size) != size){
        free(buffer);
        close(f);
        return NULL;
    }
    buffer[size] = '\0';
    close(f);
    return buffer;
}
