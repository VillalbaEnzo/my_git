/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5 [WSL: Ubuntu-24.04]
** File description:
** get_info.c
*/

#include "my.h"
#include "struct.h"

void get_infos(top_t *t)
{
    meminfo(t);
    uptime(t);
    current_time(t);
    loadavg(t);
    cpu_stat(t);
}
