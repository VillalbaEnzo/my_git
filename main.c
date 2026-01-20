/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** main.c
*/

#include "my.h"
#include "struct.h"
#include <ncurses.h>

static void call_top(top_t *t)
{
    get_infos(t);
    get_user(t);
    get_memory(t);
    get_pr_nice(t);
    clear();
    display_header(t);
    print_process_line();
    print_processses(t);
}

static void init_ncurse(void)
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
}

static void top_loop(top_t *t)
{
    int ch = 0;

    while (t->inf->running) {
        ch = getch();
        if (ch != ERR) {
            handle_input(t, ch);
            call_top(t);
        } else
            call_top(t);
    }
}

int main(int ac, char **av)
{
    top_t *t = define_top();

    if (av == NULL || ac == 0 || t == NULL || ac > 7)
        return 84;
    if (parsing_av(av, t) == 84)
        return 84;
    init_ncurse();
    timeout(t->inf->refresh_delay * 1000);
    call_top(t);
    top_loop(t);
    endwin();
    free_top(t);
    return 0;
}
