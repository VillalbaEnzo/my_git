/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5 [WSL: Ubuntu-24.04]
** File description:
** loadavg.c
*/

#include "my.h"
#include "struct.h"

static float transform_to_float(const char *integer, const char *decimal)
{
    char result[100];

    strcpy(result, integer);
    strcat(result, ".");
    strcat(result, decimal);
    return strtof(result, NULL);
}

void loadavg(top_t *t)
{
    char **buf = open_read(LOADAVG_PATH, true);

    t->sys->loadavg_1 = transform_to_float(buf[0], buf[1]);
    t->sys->loadavg_5 = transform_to_float(buf[2], buf[3]);
    t->sys->loadavg_15 = transform_to_float(buf[4], buf[5]);
    free_buf_files(buf);
    return;
}
