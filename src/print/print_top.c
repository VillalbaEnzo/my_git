/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** print_top.c
*/

#include "struct.h"
#include "my.h"

void print_set(set_t *s)
{
    if (!s)
        return;
    printf("--- SET_T ---\n");
    printf("frames=%d username=%s secondes=%f\n\n",
        s->frames, s->username, s->secondes);
}

void print_p(p_t *p)
{
    if (!p)
        return;
    printf("--- P_T ---\n");
    printf("frames=%d username=%d secondes=%d\n\n",
        p->frames, p->username, p->secondes);
}

void print_system_uptime_load(system_t *sys)
{
    printf("Time: %dh %dm %ds\n", sys->current_time_hours,
        sys->current_time_minutes, sys->current_time_secondes);
    printf("Uptime: %dd %dh %dm\n", sys->uptime_days,
        sys->uptime_hours, sys->uptime_minutes);
    printf("Load avg: %.2f %.2f %.2f\n", sys->loadavg_1,
        sys->loadavg_5, sys->loadavg_15);
}

static void print_system_cpu(system_t *sys)
{
    printf("CPU: user=%f%% sys=%f%% nice=%f%% idle=%f%%\n",
        sys->cpu_percent_user, sys->cpu_percent_system,
        sys->cpu_percent_nice, sys->cpu_percent_idle);
}

static void print_system_memory(system_t *sys)
{
    printf("Memory: %.1f/%.1f MiB (avail=%.1f buffers=%.1f cached=%.1f)\n",
        sys->mem_used / 1024.0, sys->mem_total / 1024.0,
        sys->mem_available / 1024.0, sys->mem_buffers / 1024.0,
        sys->mem_cached / 1024.0);
    printf("Swap: %.1f/%.1f MiB (cached=%.1f)\n",
        sys->swap_used / 1024.0, sys->swap_total / 1024.0,
        sys->swap_cached / 1024.0);
}

static void print_system_tasks(system_t *sys)
{
    printf("Tasks: %u, total,%u running, ",
        sys->tasks_total, sys->tasks_running);
    printf("%u sleeping, %u stopped, %u zombie\n",
        sys->tasks_sleeping, sys->tasks_stopped,
        sys->tasks_zombie);
    printf("Logged users: %u\n\n", sys->logged_users);
}

static void print_system(system_t *sys)
{
    if (!sys)
        return;
    printf("--- SYSTEM_T ---\n");
    print_system_uptime_load(sys);
    print_system_cpu(sys);
    print_system_memory(sys);
    print_system_tasks(sys);
}

static void print_inf(inf_t *inf)
{
    if (!inf)
        return;
    printf("--- INF_T ---\n");
    printf("Processes: count=%d capacity=%d\n",
        inf->process_count, inf->process_capacity);
    printf("Filter user: %s\n", inf->filter_user);
    printf("Frames: current=%d max=%d\n",
        inf->current_frame, inf->max_frames);
    printf("Refresh delay: %f\n", inf->refresh_delay);
    printf("Sort: column=%d reverse=%d\n",
        inf->sort_column, inf->sort_reverse);
    printf("Scroll: offset=%d selected_pid=%d\n",
        inf->scroll_offset, inf->selected_pid);
    printf("Terminal: %dx%d\n", inf->term_width, inf->term_height);
    printf("Flags: running=%d threads=%d forest=%d fullcmd=%d color=%d\n",
        inf->running, inf->show_threads, inf->forest_mode,
        inf->show_full_cmd, inf->color_mode);
    printf("Mem units: process=%d system=%d\n\n",
        inf->mem_unit_process, inf->mem_unit_system);
}

static void print_process(process_t *pros)
{
    if (!pros)
        return;
    printf("--- PROCESS_T ---\n");
    printf("PID=%d PPID=%d UID=%d GID=%d\n",
        pros->pid, pros->ppid, pros->uid, pros->gid);
    printf("User=%s Group=%s\n", pros->user, pros->group);
    printf("State=%c Priority=%d Nice=%d Threads=%u\n",
        pros->state, pros->priority, pros->nice,
        pros->threads);
    printf("Memory: VIRT=%lu RES=%lu SHR=%lu\n",
        pros->virt_memory, pros->res_memory,
        pros->shared_memory);
    printf("CPU=%f%% MEM=%f%%\n",
        pros->cpu_percent, pros->mem_percent);
    printf("Time=%s Command=%s\n\n",
        pros->time_str, pros->command);
}

void print_top(top_t *top)
{
    if (!top)
        return;
    printf("=== TOP_T STRUCTURE ===\n");
    printf("top=%p p=%p s=%p inf=%p pros=%p sys=%p\n\n",
        top, top->p, top->s, top->inf, top->pros, top->sys);
    print_set(top->s);
    print_p(top->p);
    print_system(top->sys);
    print_inf(top->inf);
    print_process(top->pros);
}
