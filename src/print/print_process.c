/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5
** File description:
** print_process.c
*/

#include "my.h"
#include "ncurses.h"
#include "struct.h"

void print_processses(top_t *t)
{
    process_t *proc;
    int count = 0;

    for (int i = t->inf->scroll_offset;
        i < t->inf->process_count && count < LINES - 7; i++) {
        proc = &t->inf->processes[i];
        move(7 + count, 0);
        printw(" %6d %-8s %2d %2d %7lu %6lu %6lu %c %5.1f %5.1f %9s %.40s",
            proc->pid, proc->user, proc->priority, proc->nice,
            proc->virt_memory, proc->res_memory, proc->shared_memory,
            proc->state, proc->cpu_percent, proc->mem_percent,
            proc->time_str, proc->command);
        count++;
    }
    refresh();
}
