/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** sig_handling
*/
#include "mysh.h"
#include "utils.h"

void print_sig(int sig_num)
{
    if (sig_num == SIGFPE)
        mini_printf(2, "Floating exception");
    else
        mini_printf(2, "%s", strsignal(sig_num));
}

int handle_sig(int c_status)
{
    int exit_sig = 0;

    if (WIFSTOPPED(c_status)) {
        exit_sig = WSTOPSIG(c_status);
        mini_printf(2, "%s\n", strsignal(exit_sig));
        return DEF_EXIT_SIG + exit_sig;
    }
    if (WIFSIGNALED(c_status)) {
        exit_sig = WTERMSIG(c_status);
        print_sig(exit_sig);
        if (WCOREDUMP(c_status))
            my_putstr(" (core dumped)", 2);
        my_putchar('\n', 2);
        return DEF_EXIT_SIG + exit_sig;
    }
    if (WIFEXITED(c_status))
        return (WEXITSTATUS(c_status));
    return 0;
}
