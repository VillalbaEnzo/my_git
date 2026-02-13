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
        printf("ici");
        temp = temp->next;
    }
    return len;
}

char **chained_list_to_buf(node_t *head)
{
    int len = get_len(head);
    node_t *temp = head;
    char **buf = malloc(sizeof(char *) * (len + 1));
    int idx = 0;

    if (!buf)
        return NULL;
    while (temp) {
        buf[idx] = my_strdup(temp->line);
        if (!buf[idx]) {
            free_double_buf(buf);
            return NULL;
        }
        idx++;
        temp = temp->next;
    }
    buf[idx] = NULL;
    return buf;
}

int handle_fork(char **cmd, node_t *head)
{
    pid_t pid = fork();
    int status;
    char **env = chained_list_to_buf(head);

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
