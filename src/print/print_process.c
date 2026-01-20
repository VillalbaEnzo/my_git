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
    int start_y = 7;
    int max_displayable = LINES - start_y;
    int count = 0;

    for (int i = t->inf->scroll_offset; i < t->inf->process_count
        && count < max_displayable; i++) {
        proc = &t->inf->processes[i];
        move(start_y + count, 0);
        printw("%7d %-8s %2d %3d %6lu %5lu %5lu %c %5.1f %5.1f %8s %s",
            proc->pid, proc->user, proc->priority, proc->nice,
            proc->virt_memory / 1024, proc->res_memory / 1024,
            proc->shared_memory / 1024, proc->state, proc->cpu_percent,
            proc->mem_percent, proc->time_str, proc->command
        );
        count++;
    }
    refresh();
}
