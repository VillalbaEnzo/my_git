/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5
** File description:
** get_states.c
*/
#include "struct.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "math.h"

static int read_stat_file(int pid, char *buf, size_t size)
{
    char path[64];
    FILE *f;

    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
    f = fopen(path, "r");
    if (!f)
        return 0;
    if (!fgets(buf, size, f)) {
        fclose(f);
        return 0;
    }
    fclose(f);
    return 1;
}

static void get_total_f(unsigned long long *total)
{
    FILE *f = fopen("/proc/stat", "r");

    if (!f)
        return;
    fscanf(f, "cpu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
        &total[0], &total[1], &total[2], &total[3], &total[4],
        &total[5], &total[6], &total[7], &total[8], &total[9]);
    fclose(f);
}

static void get_meminfo(unsigned long *m)
{
    FILE *f = fopen("/proc/meminfo", "r");
    char line[256];

    *m = 0;
    if (!f)
        return;
    while (fgets(line, sizeof(line), f))
        if (sscanf(line, "MemTotal: %lu", m) == 1)
            break;
    fclose(f);
}

static void parse_process_times(process_t *p, const char *b)
{
    char *ptr = strchr(b, ')');

    if (!ptr)
        return;
    ptr++;
    sscanf(ptr,
        " %c %*d %*d %*d %*d %*d "
        "%*u %*u %*u %*u %*u "
        "%lu %lu %*lu %*lu "
        "%*d %*d %u %*d %lu",
        &p->state, &p->utime, &p->stime,
        &p->threads, &p->starttime);
}

static void compute_time(process_t *p)
{
    long hz = sysconf(_SC_CLK_TCK);
    unsigned long t = p->utime + p->stime;
    float sec = (float)t / (float)hz;
    int m = (int)sec / 60;
    float s = sec - m * 60;

    snprintf(p->time_str, sizeof(p->time_str),
        "%02d:%05.2f", m, s);
}

static void compute_mem(process_t *p)
{
    unsigned long total;
    long ps;
    unsigned long rss_b;

    get_meminfo(&total);
    if (!total)
        return;
    ps = sysconf(_SC_PAGESIZE);
    rss_b = p->res_memory * ps;
    p->mem_percent =
        (float)rss_b / (float)(total * 1024) * 100.0;
}

static void compute_cpu(process_t *p)
{
    unsigned long long t[10];
    unsigned long long now = 0;
    unsigned long long proc_now;
    unsigned long long delta_p;
    unsigned long long delta_t;

    get_total_f(t);
    for (int i = 0; i < 10; i++)
        now += t[i];
    proc_now = p->utime + p->stime;
    delta_p = proc_now - p->old_utime - p->old_stime;
    delta_t = now - p->old_total;
    if (delta_t > 0)
        p->cpu_percent = (float)delta_p / (float)delta_t * 100.0;
    p->cpu_percent = ceilf(p->cpu_percent * 10.0f) / 10.0f;
    p->old_utime = p->utime;
    p->old_stime = p->stime;
    p->old_total = now;
}

void get_states_cpup_memep_time(process_t *p)
{
    char buf[2048];

    if (!p)
        return;
    if (!read_stat_file(p->pid, buf, sizeof(buf)))
        return;
    parse_process_times(p, buf);
    compute_time(p);
    compute_cpu(p);
    compute_mem(p);
}
