/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** handle_fork.c
*/

#include "my.h"

int handle_fork(char **cmd, char **env)
{
    pid_t pid = fork();
    int status;

    if (pid < 0) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        execve(cmd[0], cmd, env);
        perror("execve");
        exit(1);
    } else
        waitpid(pid, &status, 0);
    return 0;
}
    // if (WIFEXITED(status))
    //     printf("Enfant terminé avec code %d\n", WEXITSTATUS(status));
