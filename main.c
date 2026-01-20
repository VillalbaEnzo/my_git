/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** main.c
*/

#include "my.h"
#include "struct.h"

static void call_top(top_t *t)
{
    clear();
    get_infos(t);
    display_header(t);
    print_process_line();
    get_user(t);
    get_memory(t);
    print_processses(t);
}

void handle_input(top_t *t)
{
    int ch = getch();

    timeout((int)(t->inf->refresh_delay * 1000));
    if (ch == ERR)
        return;
    switch (ch) {
        case 'q':
            t->inf->running = 0;
            break;
        case 'e':
            t->inf->mem_unit_process = (t->inf->mem_unit_process + 1) % 2;
            break;
        case KEY_UP:
            if (t->inf->scroll_offset > 0)
                t->inf->scroll_offset--;
            break;
        case KEY_DOWN:
            if (t->inf->scroll_offset < t->inf->process_count - 1)
                t->inf->scroll_offset++;
            break;
        case 'k':
            break;
    }
}

int main(int ac, char **av)
{
    top_t *t = define_top();

    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    if (av == NULL || ac == 0 || t == NULL || ac > 7)
        return 84;
    if (parsing_av(av, t) == 84)
        return 84;
    while (t->inf->running) {
        call_top(t);
        handle_input(t);
    }
    endwin();
    free_top(t);
    return 0;
}
