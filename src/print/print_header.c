/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5
** File description:
** print_header.c
*/

#include <ncurses.h>
#include "struct.h"
#include "my.h"

static void print_uptime_minutes(system_t *s)
{
    mvprintw(0, 0, "top - %02d:%02d:%02d up %d min,  %d users,  "
        "load average: %.2f, %.2f, %.2f",
        s->current_time_hours, s->current_time_minutes,
        s->current_time_secondes,
        s->uptime_minutes,
        s->logged_users,
        s->loadavg_1, s->loadavg_5, s->loadavg_15);
}

static void print_uptime_hours(system_t *s)
{
    mvprintw(0, 0, "top - %02d:%02d:%02d up %02d:%02d,  %d users,  "
        "load average: %.2f, %.2f, %.2f",
        s->current_time_hours, s->current_time_minutes,
        s->current_time_secondes,
        s->uptime_hours, s->uptime_minutes,
        s->logged_users,
        s->loadavg_1, s->loadavg_5, s->loadavg_15);
}

static void print_uptime_days(system_t *s)
{
    mvprintw(0, 0, "top - %02d:%02d:%02d up %d days, %02d:%02d,  %d users,  "
        "load average: %.2f, %.2f, %.2f",
        s->current_time_hours, s->current_time_minutes,
        s->current_time_secondes,
        s->uptime_days, s->uptime_hours, s->uptime_minutes,
        s->logged_users,
        s->loadavg_1, s->loadavg_5, s->loadavg_15);
}

static void print_tasks(system_t *s)
{
    mvprintw(1, 0, "Tasks: %3d total, %3d running, %3d sleeping, "
        "%3d stopped, %3d zombie",
        s->tasks_total,
        s->tasks_running,
        s->tasks_sleeping,
        s->tasks_stopped,
        s->tasks_zombie);
}

static void print_cpu(system_t *s)
{
    mvprintw(2, 0, "%%Cpu(s): %4.1f us, %4.1f sy, %4.1f ni, %4.1f id, "
        "%4.1f wa, %4.1f hi, %4.1f si, %4.1f st",
        s->cpu_percent_user, s->cpu_percent_system,
        s->cpu_percent_nice, s->cpu_percent_idle,
        s->cpu_percent_iowait, s->cpu_percent_irq,
        s->cpu_percent_softirq, s->cpu_percent_steal);
}

static void print_memory(system_t *s)
{
    mvprintw(3, 0, "MiB Mem : %6.1f total, %6.1f free, %6.1f used, "
        "%6.1f buff/cache",
        s->mem_total / 1024.0, s->mem_free / 1024.0,
        s->mem_used / 1024.0, s->mem_buff_cache / 1024.0);
    mvprintw(4, 0, "MiB Swap: %6.1f total, %6.1f free, %6.1f used. "
        "%6.1f avail Mem",
        s->swap_total / 1024.0, s->swap_free / 1024.0,
        s->swap_used / 1024.0, s->mem_available / 1024.0);
}

void display_header(top_t *t)
{
    print_uptime_minutes(t->sys);
    if (t->sys->uptime_minutes >= 60)
        print_uptime_hours(t->sys);
    if (t->sys->uptime_hours >= 24)
        print_uptime_days(t->sys);
    print_tasks(t->sys);
    print_cpu(t->sys);
    print_memory(t->sys);
    refresh();
}
