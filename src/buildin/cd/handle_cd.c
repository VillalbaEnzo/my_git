/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell1-5
** File description:
** handle_cd.c
*/

#include "my.h"

static void update_env(shell_t *shell, char *old_pwd)
{
    char *cwd = getcwd(NULL, 0);
    char *arg_pwd[] = {"setenv", "PWD", cwd, NULL};
    char *arg_old[] = {"setenv", "OLDPWD", old_pwd, NULL};

    set_env(arg_pwd, shell);
    set_env(arg_old, shell);
    free(cwd);
}

static void home_cd(shell_t *shell)
{
    char *old_pwd = getcwd(NULL, 0);
    node_t *temp = shell->env;

    while (temp) {
        if (my_strncmp(temp->line, "HOME=", 5) == 0) {
            chdir(temp->line + 5);
            update_env(shell, old_pwd);
            free(old_pwd);
            return;
        }
        temp = temp->next;
    }
    write(2, "cd: No home directory.\n", 24);
}

static void old_path_cd(shell_t *shell)
{
    char *old_pwd = getcwd(NULL, 0);
    node_t *temp = shell->env;

    while (temp) {
        if (my_strncmp(temp->line, "OLDPWD=", 7) == 0) {
            chdir(temp->line + 7);
            update_env(shell, old_pwd);
            free(old_pwd);
            return;
        }
        temp = temp->next;
    }
    write(2, "cd: OLDPWD not set.\n", 21);
}

void normal_cd(char **cmd, shell_t *shell)
{
    char *old_pwd = getcwd(NULL, 0);

    if (chdir(cmd[1]) == 0) {
        update_env(shell, old_pwd);
        free(old_pwd);
        return;
    }
    free(old_pwd);
    write(2, cmd[1], my_strlen(cmd[1]));
    write(2, ": No such file or directory.\n", 30);
}

void handle_cd(char **cmd, shell_t *shell)
{
    if (!cmd[1]) {
        home_cd(shell);
        return;
    }
    if (cmd[2]) {
        write(2, "cd: Too many arguments.\n", 25);
        return;
    }
    if (cmd[1] && my_strlen(cmd[1]) == 1 && cmd[1][0] == '-') {
        old_path_cd(shell);
        return;
    }
    normal_cd(cmd, shell);
    return;
}
