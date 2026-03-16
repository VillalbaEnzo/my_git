/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** sh.c
*/

#include "my.h"
#include "buildin.h"

static int exit_sh(char **cmd)
{
    if ((cmd && cmd[0] && my_strcmp(cmd[0], "exit") == 0)) {
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

static int process_one_cmd(char *cmd, shell_t *shell)
{
    char *clean_cmd = trim(cmd);
    char **piped_cmd = NULL;
    char **cmds = NULL;

    if (!clean_cmd)
        return 0;
    cmds = split(clean_cmd, " \t");
    piped_cmd = split(cmds, "|");
    if (cmds && cmds[0]) {
        if (exit_sh(cmds) == 1) {
            free(clean_cmd);
            return 1;
        }
        exec_cmd(cmds, shell);
    }
    if (cmds)
        free_double_buf(cmds);
    free(clean_cmd);
    return 0;
}

static int process_all_cmd(char **cmd, shell_t *shell)
{
    int exit_status = 0;

    for (int i = 0; cmd[i]; i++) {
        exit_status = process_one_cmd(cmd[i], shell);
        if (exit_status == 1)
            return 1;
    }
    return 0;
}

void handle_sh(shell_t *shell)
{
    size_t len = 0;
    char **cmd = NULL;
    char *line = NULL;

    while (1) {
        if (isatty(0))
            mini_printf("$> ");
        if (getline(&line, &len, stdin) == -1)
            break;
        cmd = split(line, ";\n");
        if (!cmd)
            continue;
        if (process_all_cmd(cmd, shell) == 1) {
            free_double_buf(cmd);
            break;
        }
        free_double_buf(cmd);
    }
    free(line);
}
