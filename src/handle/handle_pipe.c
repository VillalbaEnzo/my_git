/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell2-7 [WSL: Ubuntu-24.04]
** File description:
** handle_pipe.c
*/

#include "my.h"

void exec_pipeline(char **piped_cmd, shell_t *shell)
{
    int fd[2];
    int prev_fd = 0;
    pid_t pid;
    int status;
    char **cmds = NULL;

    for (int i = 0; piped_cmd[i]; i++) {
        if (piped_cmd[i + 1])
            pipe(fd);
        pid = fork();
        if (pid == 0) {
            if (prev_fd != 0) {
                dup2(prev_fd, 0);
                close(prev_fd);
            }
            if (piped_cmd[i + 1]) {
                dup2(fd[1], 1);
                close(fd[1]);
                close(fd[0]);
            }
            cmds = split(piped_cmd[i], " \t");
            shell->env_cp = chained_list_to_buf(shell->env);
            handle_path(shell, cmds);
            execve(cmds[0], cmds, shell->env_cp);
            exit(1);
        }
        if (prev_fd != 0)
            close(prev_fd);
        if (cmds[i + 1]) {
            close(fd[1]);
            prev_fd = fd[0];
        }
    }
    while (waitpid(-1, &status, 0) > 0);
}
