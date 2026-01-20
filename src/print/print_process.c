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

    move(7, 0);
    for (int i = 0; i < t->inf->process_count; i++) {
        proc = &t->inf->processes[i];
        printw("%7d %-9s %3d %3d %zu %zu %zu\n",
            proc->pid, proc->user, proc->priority,
            proc->nice, proc->virt_memory,
            proc->res_memory,
            proc->shared_memory);
    }
    refresh();
}
