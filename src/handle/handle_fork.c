/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** handle_fork.c
*/

#include "my.h"

static int get_len(node_t *head)
{
    int len = 0;
    node_t *temp = head;

    while (temp) {
        len++;
        temp = temp->next;
    }
    return len;
}

static char **chained_list_to_buf(node_t *head)
{
    int len = get_len(head);
    node_t *temp = head;
    char **buf = malloc(sizeof(char *) * (len + 1));
    int idx = 0;

    if (!buf)
        return NULL;
    while (temp) {
        buf[idx] = my_strdup(temp->line);
        idx++;
        temp = temp->next;
    }
    buf[idx] = NULL;
    return buf;
}

static void update_status(int status, shell_t *shell)
{
    if (WIFEXITED(status))
        shell->last_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        shell->last_status = 128 + WTERMSIG(status);
}

static void exec_child(char **cmd, char **env)
{
    if (execve(cmd[0], cmd, env) == -1) {
        write(2, cmd[0], my_strlen(cmd[0]));
        write(2, ": Command not found.\n", 21);
        exit(1);
    }
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
