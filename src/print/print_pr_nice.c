/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5
** File description:
** print_pr_nice.c
*/

#include "my.h"
#include "ncurses.h"
#include "struct.h"

void print_pr_nice(top_t *t)
{
    process_t *proc;

    move(7, 0);
    for (int i = 0; i < t->inf->process_count; i++) {
        proc = &t->inf->processes[i];
        printw("%d %d\n", proc->priority, proc->nice);
    }
    refresh();
}
