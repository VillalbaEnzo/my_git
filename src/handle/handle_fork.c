/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** handle_fork.c
*/

#include "my.h"

static void print_sig_error(int status)
{
    int sig = WTERMSIG(status);

    if (sig == 8)
        write(2, "Floating exception", 18);
    else
        write(2, strsignal(sig), my_strlen(strsignal(sig)));
    if (WCOREDUMP(status))
        write(2, " (core dumped)", 14);
    write(2, "\n", 1);
}

static void update_status(int status, shell_t *shell)
{
    if (WIFEXITED(status)) {
        shell->last_status = WEXITSTATUS(status);
        return;
    }
    if (WIFSIGNALED(status)) {
        shell->last_status = 128 + WTERMSIG(status);
        print_sig_error(status);
    }
}

static void exec_child(char **cmd, char **env)
{
    execve(cmd[0], cmd, env);
    if (errno == EACCES) {
        write(2, cmd[0], my_strlen(cmd[0]));
        write(2, ": Permission denied.\n", 21);
        exit(126);
    } else if (errno == ENOEXEC) {
        write(2, cmd[0], my_strlen(cmd[0]));
        write(2, ": Exec format error. Wrong Architecture.\n", 41);
        exit(126);
    } else {
        write(2, cmd[0], my_strlen(cmd[0]));
        write(2, ": Command not found.\n", 21);
    }
    exit(1);
}

int handle_fork(char **cmd, shell_t *shell)
{
    pid_t pid;
    int status;

    shell->env_cp = chained_list_to_buf(shell->env);
    if (!shell->env_cp)
        return 1;
    pid = fork();
    if (pid < 0) {
        perror("fork");
        free_double_buf(shell->env_cp);
        return 1;
    }
    if (pid == 0)
        exec_child(cmd, shell->env_cp);
    waitpid(pid, &status, 0);
    update_status(status, shell);
    free_double_buf(shell->env_cp);
    return 0;
}
