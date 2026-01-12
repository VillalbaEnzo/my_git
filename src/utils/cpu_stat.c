/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5
** File description:
** stat.c
*/

#include "my.h"
#include "struct.h"

void cpu_stat(top_t *t)
{
    char **buf = open_read(STAT_PATH, true);

    for (int i = 0; buf[i]; i++) {
        if (strncmp(buf[i], "cpu\0", 4) == 0) {
            t->sys->cpu_user = atoi(buf[i + 1]);
            t->sys->cpu_nice = atoi(buf[i + 2]);
            t->sys->cpu_system = atoi(buf[i + 3]);
            t->sys->cpu_idle = atoi(buf[i + 4]);
            t->sys->cpu_iowait = atoi(buf[i + 5]);
            t->sys->cpu_irq = atoi(buf[i + 6]);
            t->sys->cpu_softirq = atoi(buf[i + 7]);
            t->sys->cpu_steal = atoi(buf[i + 8]);
            t->sys->cpu_guest = atoi(buf[i + 9]);
            t->sys->cpu_guest_nice = atoi(buf[i + 10]);
            break;
        }
    }
    free_buf_files(buf);
    printf("%llu", t->sys->cpu_user);
}