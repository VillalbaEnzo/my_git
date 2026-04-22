/*
** EPITECH PROJECT, 2026
** minishell2 [WSL: Ubuntu]
** File description:
** redirections_save
*/

#include "as_tree.h"
#include "mysh.h"

void reset_stdin(redir_t *redirection)
{
    if (dup2(redirection->save, 0) == -1)
        perror("dup2");
    else
        close(redirection->save);
}

void reset_stdout(redir_t *redirection)
{
    if (dup2(redirection->save, 1) == -1)
        perror("dup2");
    else
        close(redirection->save);
}

void reset_fds(redir_t *redir_array, int redir_count)
{
    for (int i = 0; i < redir_count; i++) {
        switch (redir_array[i].type) {
            case SIMPLE_L:
            case DOUBLE_L:
                reset_stdin(&redir_array[i]);
            case SIMPLE_R:
            case DOUBLE_R:
                reset_stdout(&redir_array[i]);
            case NOT_R:
                return;
        }
    }
}
