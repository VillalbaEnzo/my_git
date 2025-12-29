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
    my_printf("--- SET_T ---\n");
    my_printf("frames=%d username=%s secondes=%f\n\n",
        s->frames, s->username, s->secondes);
}

void print_p(p_t *p)
{
    if (!p)
        return;
    my_printf("--- P_T ---\n");
    my_printf("frames=%d username=%d secondes=%d\n\n",
        p->frames, p->username, p->secondes);
}

void print_system_uptime_load(system_t *sys)
{
    my_printf("Uptime: %dd %dh %dm\n", sys->uptime_days,
        sys->uptime_hours, sys->uptime_minutes);
    my_printf("Load avg: %f %f %f\n", sys->loadavg_1,
        sys->loadavg_5, sys->loadavg_15);
}

static void print_system_cpu(system_t *sys)
{
    my_printf("CPU: user=%f%% sys=%f%% nice=%f%% idle=%f%%\n",
        sys->cpu_percent_user, sys->cpu_percent_system,
        sys->cpu_percent_nice, sys->cpu_percent_idle);
}

static void print_system_memory(system_t *sys)
{
    my_printf("Memory: %lu/%lu (avail=%lu buffers=%lu cached=%lu)\n",
        sys->mem_used, sys->mem_total, sys->mem_available,
        sys->mem_buffers, sys->mem_cached);
    my_printf("Swap: %lu/%lu (cached=%lu)\n", sys->swap_used,
        sys->swap_total, sys->swap_cached);
}

static void print_system_tasks(system_t *sys)
{
    my_printf("Tasks: %u total,%u running,%u ",
        sys->tasks_total, sys->tasks_running);
    my_printf("sleeping, %u stopped, %u zombie\n",
        sys->tasks_sleeping, sys->tasks_stopped,
        sys->tasks_zombie);
    my_printf("Logged users: %u\n\n", sys->logged_users);
}

static void print_system(system_t *sys)
{
    if (!sys)
        return;
    my_printf("--- SYSTEM_T ---\n");
    print_system_uptime_load(sys);
    print_system_cpu(sys);
    print_system_memory(sys);
    print_system_tasks(sys);
}

static void print_inf(inf_t *inf)
{
    if (!inf)
        return;
    my_printf("--- INF_T ---\n");
    my_printf("Processes: count=%d capacity=%d\n",
        inf->process_count, inf->process_capacity);
    my_printf("Filter user: %s\n", inf->filter_user);
    my_printf("Frames: current=%d max=%d\n",
        inf->current_frame, inf->max_frames);
    my_printf("Refresh delay: %f\n", inf->refresh_delay);
    my_printf("Sort: column=%d reverse=%d\n",
        inf->sort_column, inf->sort_reverse);
    my_printf("Scroll: offset=%d selected_pid=%d\n",
        inf->scroll_offset, inf->selected_pid);
    my_printf("Terminal: %dx%d\n", inf->term_width, inf->term_height);
    my_printf("Flags: running=%d threads=%d forest=%d fullcmd=%d color=%d\n",
        inf->running, inf->show_threads, inf->forest_mode,
        inf->show_full_cmd, inf->color_mode);
    my_printf("Mem units: process=%d system=%d\n\n",
        inf->mem_unit_process, inf->mem_unit_system);
}

static void print_process(process_t *pros)
{
    if (!pros)
        return;
    my_printf("--- PROCESS_T ---\n");
    my_printf("PID=%d PPID=%d UID=%d GID=%d\n",
        pros->pid, pros->ppid, pros->uid, pros->gid);
    my_printf("User=%s Group=%s\n", pros->user, pros->group);
    my_printf("State=%c Priority=%d Nice=%d Threads=%u\n",
        pros->state, pros->priority, pros->nice,
        pros->threads);
    my_printf("Memory: VIRT=%lu RES=%lu SHR=%lu\n",
        pros->virt_memory, pros->res_memory,
        pros->shared_memory);
    my_printf("CPU=%f%% MEM=%f%%\n",
        pros->cpu_percent, pros->mem_percent);
    my_printf("Time=%s Command=%s\n\n",
        pros->time_str, pros->command);
}

void print_top(top_t *top)
{
    if (!top)
        return;
    my_printf("=== TOP_T STRUCTURE ===\n");
    my_printf("top=%p p=%p s=%p inf=%p pros=%p sys=%p\n\n",
        top, top->p, top->s, top->inf, top->pros, top->sys);
    print_set(top->s);
    print_p(top->p);
    print_system(top->sys);
    print_inf(top->inf);
    print_process(top->pros);
}
