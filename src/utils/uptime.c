/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5 [WSL: Ubuntu-24.04]
** File description:
** sec_uptime.c
*/

#include "my.h"
#include "struct.h"

static void calcul_time(int seconds, top_t *t)
{
    while (seconds >= 60) {
        if (seconds >= 60) {
            t->sys->uptime_minutes = seconds / 60;
            seconds = seconds % 60;
        }
        if (t->sys->uptime_minutes >= 60) {
            t->sys->uptime_hours = t->sys->uptime_minutes / 60;
            t->sys->uptime_minutes = t->sys->uptime_minutes % 60;
        }
        if (t->sys->uptime_hours >= 24) {
            t->sys->uptime_days = t->sys->uptime_hours / 24;
            t->sys->uptime_hours = t->sys->uptime_hours % 24;
        }
    }
}

void uptime(top_t *t)
{
    char **sec = open_read(UPTIME_PATH, true);
    int seconds = atoi(sec[0]);

    if ((!sec || !sec[0]) && sec) {
        free(sec);
        return;
    }
    calcul_time(seconds, t);
    free_buf_files(sec);
    return;
}
