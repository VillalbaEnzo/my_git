/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** sh.c
*/

#include "my.h"

static int exit_sh(char **cmd, ssize_t ret)
{
    if ((cmd[0] && my_strcmp(cmd[0], "exit") == 0) || ret == -1) {
        free_double_buf(cmd);
        return 1;
    }
    return 0;
}

static int check_buildin(char **cmd, node_t *head)
{
    char *buildin[] = {"env", "setenv", "unsetenv", "cd", NULL};

    if (!cmd || !cmd[0])
        return 0;
    for (int i = 0; buildin[i]; i++) {
        if (my_strcmp(cmd[0], buildin[i]) == 0)
            handle_buildins(cmd, i, head);
    }
    return 0;
}

int handle_sh(node_t *head, char **env)
{
    size_t len = 0;
    ssize_t ret;
    char **cmd = NULL;
    char *line = NULL;

    while (1) {
        mini_printf("$> ");
        ret = getline(&line, &len, stdin);
        if (ret == -1)
            break;
        cmd = str_to_tab(line);
        if (exit_sh(cmd, ret))
            break;
        if (!check_buildin(cmd, head) && my_strcmp(cmd[0], "env")) {
            handle_path(head, cmd);
            handle_fork(cmd, env);
        }
        free_double_buf(cmd);
    }
    free(line);
    return 0;
}
