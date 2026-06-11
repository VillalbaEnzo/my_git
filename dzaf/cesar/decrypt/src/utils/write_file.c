/*
** EPITECH PROJECT, 2025
** next
** File description:
** main.c
*/

#include "my.h"

int write_file(char *str)
{
    FILE *fd = fopen(SAVE_FILE, "w");

    if (!fd)
        return 0;
    fwrite(str, 1, strlen(str), fd);
    chmod(SAVE_FILE, S_IRUSR | S_IRGRP | S_IROTH);
    fclose(fd);
    return 1;
}
