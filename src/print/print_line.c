/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5
** File description:
** print_line.c
*/

#include "my.h"
#include "struct.h"
#include <ncurses.h>


void print_process_line(void)
{
    attron(A_REVERSE);
    printw("\n");
    printw(" %6s %-8s %2s %2s %7s %6s %6s %1s %5s %5s %9s %s",
        "PID", "USER", "PR", "NI", "VIRT", "RES", "SHR",
        "S", "%CPU", "%MEM", "TIME+", "COMMAND");
    attroff(A_REVERSE);
    refresh();
}
