/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5
** File description:
** stat.c
*/

#include "my.h"
#include "struct.h"

static void save_prev_values(top_t *t, unsigned long long total)
{
    t->inf->old_total = total;
    t->inf->old_user = t->sys->cpu_user;
    t->inf->old_nice = t->sys->cpu_nice;
    t->inf->old_system = t->sys->cpu_system;
    t->inf->old_idle = t->sys->cpu_idle;
    t->inf->old_iowait = t->sys->cpu_iowait;
    t->inf->old_irq = t->sys->cpu_irq;
    t->inf->old_softirq = t->sys->cpu_softirq;
    t->inf->old_steal = t->sys->cpu_steal;
}

static void get_cpu_stat(top_t *t, char **buf, int i)
{
    t->sys->cpu_user = atoll(buf[i + 1]);
    t->sys->cpu_nice = atoll(buf[i + 2]);
    t->sys->cpu_system = atoll(buf[i + 3]);
    t->sys->cpu_idle = atoll(buf[i + 4]);
    t->sys->cpu_iowait = atoll(buf[i + 5]);
    t->sys->cpu_irq = atoll(buf[i + 6]);
    t->sys->cpu_softirq = atoll(buf[i + 7]);
    t->sys->cpu_steal = atoll(buf[i + 8]);
    t->sys->cpu_guest = atoll(buf[i + 9]);
    t->sys->cpu_guest_nice = atoll(buf[i + 10]);
}

static unsigned long long total_calcul(top_t *t)
{
    return t->sys->cpu_user + t->sys->cpu_nice + t->sys->cpu_system +
        t->sys->cpu_idle + t->sys->cpu_iowait + t->sys->cpu_irq +
        t->sys->cpu_softirq + t->sys->cpu_steal;
}

static void cpu_percent_calcul(top_t *t, unsigned long long diff_total)
{
    t->sys->cpu_percent_user = (float)(t->sys->cpu_user -
        t->inf->old_user) / diff_total * 100.0;
    t->sys->cpu_percent_system = (float)(t->sys->cpu_system -
        t->inf->old_system) / diff_total * 100.0;
    t->sys->cpu_percent_nice = (float)(t->sys->cpu_nice -
        t->inf->old_nice) / diff_total * 100.0;
    t->sys->cpu_percent_idle = (float)(t->sys->cpu_idle -
        t->inf->old_idle) / diff_total * 100.0;
    t->sys->cpu_percent_iowait = (float)(t->sys->cpu_iowait -
        t->inf->old_iowait) / diff_total * 100.0;
    t->sys->cpu_percent_irq = (float)(t->sys->cpu_irq -
        t->inf->old_irq) / diff_total * 100.0;
    t->sys->cpu_percent_softirq = (float)(t->sys->cpu_softirq -
        t->inf->old_softirq) / diff_total * 100.0;
    t->sys->cpu_percent_steal = (float)(t->sys->cpu_steal -
        t->inf->old_steal) / diff_total * 100.0;
}

void cpu_stat(top_t *t)
{
    char **buf = open_read(STAT_PATH, true);
    unsigned long long total = 0;
    unsigned long long diff_total = 0;

    for (int i = 0; buf[i]; i++) {
        if (strncmp(buf[i], "cpu\0", 4) == 0) {
            get_cpu_stat(t, buf, i);
            break;
        }
    }
    free_buf_files(buf);
    total = total_calcul(t);
    diff_total = total - t->inf->old_total;
    if (diff_total == 0) {
        save_prev_values(t, total);
        return;
    }
    cpu_percent_calcul(t, diff_total);
    save_prev_values(t, total);
}
