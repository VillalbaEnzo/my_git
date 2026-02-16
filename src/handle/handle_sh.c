/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** sh.c
*/

#include "my.h"
#include "buildin.h"

static int exit_sh(char **cmd, ssize_t ret)
{
    if ((cmd[0] && my_strcmp(cmd[0], "exit") == 0) || ret == -1) {
        free_double_buf(cmd);
        return 1;
    }
    return 0;
}

static int check_buildin(char **cmd, shell_t *shell)
{
    if (!cmd || !cmd[0])
        return 0;
    for (int i = 0; buildin[i]; i++) {
        if (my_strcmp(cmd[0], buildin[i]) == 0) {
            handle_buildins(cmd, i, shell);
            return 1;
        }
    }
    return 0;
}

static void exec_cmd(char **cmd, shell_t *shell)
{
    if (!check_buildin(cmd, shell)) {
        handle_path(shell, cmd);
        handle_fork(cmd, shell);
    }
}

void handle_sh(shell_t *shell)
{
    size_t len = 0;
    ssize_t ret;
    char **cmd = NULL;
    char *line = NULL;

    while (1) {
        if (isatty(0))
            mini_printf("$> ");
        ret = getline(&line, &len, stdin);
        if (ret == -1)
            break;
        cmd = str_to_tab(line);
        if (exit_sh(cmd, ret))
            break;
        exec_cmd(cmd, shell);
        free_double_buf(cmd);
    }
    free(line);
}
