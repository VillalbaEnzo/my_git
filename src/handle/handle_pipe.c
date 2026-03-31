/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell2-7 [WSL: Ubuntu-24.04]
** File description:
** handle_pipe.c
*/

#include "my.h"

struct contexte_s {
    char **piped_cmd;
    int fd[2];
    int prev_fd;
    int i;
    char **cmds;
};

static void children_exec(struct contexte_s *contexte, shell_t *shell)
{
    char *spaced_cmd = NULL;

    if (contexte->prev_fd != 0) {
        dup2(contexte->prev_fd, 0);
        close(contexte->prev_fd);
    }
    if (contexte->piped_cmd[contexte->i + 1]) {
        dup2(contexte->fd[1], 1);
        close(contexte->fd[1]);
        close(contexte->fd[0]);
    }
    spaced_cmd = handle_add_spaces(contexte->piped_cmd[contexte->i]);
    contexte->cmds = split(spaced_cmd, " \t");
    shell->env_cp = chained_list_to_buf(shell->env);
    handle_redirection(contexte->cmds);
    handle_path(shell, contexte->cmds);
    if (check_buildin(contexte->cmds, shell))
        exit(0);
    else my_execve(contexte->cmds, shell->env_cp);
    free(spaced_cmd);
}

void exec_pipeline(char **piped_cmd, shell_t *shell)
{
    struct contexte_s contexte = {piped_cmd, {0}, 0};
    int status;

    for (contexte.i = 0; piped_cmd[contexte.i]; contexte.i++) {
        if (piped_cmd[contexte.i + 1])
            pipe(contexte.fd);
        if (fork() == 0) {
            children_exec(&contexte, shell);
        }
        if (contexte.prev_fd != 0)
            close(contexte.prev_fd);
        if (piped_cmd[contexte.i + 1]) {
            close(contexte.fd[1]);
            contexte.prev_fd = contexte.fd[0];
        }
    }
    while (waitpid(-1, &status, 0) > 0);
}
