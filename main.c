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
    sleep(t->inf->refresh_delay);
}

int main(int ac, char **av)
{
    top_t *t = define_top();

    initscr();
    cbreak();
    if (av == NULL || ac == 0 || t == NULL || ac > 7)
        return 84;
    if (parsing_av(av, t) == 84)
        return 84;
    while (1) {
        call_top(t);
    }
    endwin();
    free(t);
    return 0;
}
