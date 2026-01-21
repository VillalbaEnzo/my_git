/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5
** File description:
** time.c
*/

#include "my.h"
#include "struct.h"

void current_time(top_t *t)
{
    struct tm *tm;

    t->sys->current_time = time(NULL);
    tm = localtime(&t->sys->current_time);
    t->sys->current_time_secondes = tm->tm_sec;
    t->sys->current_time_minutes = tm->tm_min;
    t->sys->current_time_hours = tm->tm_hour;
    return;
}
