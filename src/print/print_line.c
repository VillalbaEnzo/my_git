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
    move(6, 0);
    printw("%s",
        "    PID USER    PR  NI   VIRT   RES   SHR S  %CPU  %MEM    TIME+ ");
    attroff(A_REVERSE);
    refresh();
}
