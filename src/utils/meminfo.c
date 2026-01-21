/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5
** File description:
** meminfo.c
*/

#include "my.h"
#include "struct.h"

static void get_fixed_value(top_t *t, char **buf)
{
    for (int i = 0; buf[i]; i++) {
        if (strcmp(buf[i], "MemTotal") == 0)
            t->sys->mem_total = atoi(buf[i + 1]);
        if (strcmp(buf[i], "MemFree") == 0)
            t->sys->mem_free = atoi(buf[i + 1]);
        if (strcmp(buf[i], "MemAvailable") == 0)
            t->sys->mem_available = atoi(buf[i + 1]);
        if (strcmp(buf[i], "Buffers") == 0)
            t->sys->mem_buffers = atoi(buf[i + 1]);
        if (strcmp(buf[i], "Cached") == 0)
            t->sys->mem_cached = atoi(buf[i + 1]);
        if (strcmp(buf[i], "SwapTotal") == 0)
            t->sys->swap_total = atoi(buf[i + 1]);
        if (strcmp(buf[i], "SwapFree") == 0)
            t->sys->swap_free = atoi(buf[i + 1]);
        if (strcmp(buf[i], "SwapCached") == 0)
            t->sys->swap_cached = atoi(buf[i + 1]);
    }
}

static void get_calculate_value(top_t *t)
{
    t->sys->swap_used = t->sys->swap_total - t->sys->swap_free;
    t->sys->mem_buff_cache = t->sys->mem_buffers + t->sys->mem_cached;
    t->sys->mem_used = t->sys->mem_total - t->sys->mem_available;
}

void meminfo(top_t *t)
{
    char **buf = open_read(MEMINFO_PATH, true);

    get_fixed_value(t, buf);
    get_calculate_value(t);
    free_buf_files(buf);
}
