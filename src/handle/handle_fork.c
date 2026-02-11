/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** handle_fork.c
*/

#include "my.h"

int handle_fork(char *path, char **cmd, char **env)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        execve(path, cmd + 1, env);
        perror("execve");
        exit(1);
    }
    else {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
            printf("Enfant terminé avec code %d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("Enfant tué par signal %d\n", WTERMSIG(status));
    }
    return 0;
}
