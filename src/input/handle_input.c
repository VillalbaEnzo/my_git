/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5 [WSL: Ubuntu-24.04]
** File description:
** handle_input.c
*/

#include "my.h"
#include "struct.h"
#include <ncurses.h>

void handle_input(top_t *t, int ch)
{
    switch (ch) {
        case 'q':
            t->inf->running = 0;
            break;
        default:
            break;
    }
}
