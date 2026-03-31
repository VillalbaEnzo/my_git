/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell1-5
** File description:
** unsetenv.c
*/

#include "my.h"

static char *create_env_line(char *name, char *value)
{
    int len = 0;
    char *new_line = NULL;

    len += my_strlen(name) + 2;
    if (value)
        len += my_strlen(value);
    new_line = malloc(sizeof(char) * len);
    if (!new_line)
        return NULL;
    my_strcpy(new_line, name);
    my_strcat(new_line, "=");
    if (value)
        my_strcat(new_line, value);
    return new_line;
}

static int env_error(char **cmd, shell_t *shell)
{
    if (cmd[2] && cmd[3]) {
        write(2, "setenv: Too many arguments.\n", 28);
        shell->last_status = 1;
        return 1;
    }
    if (!is_alpha(NULL, cmd[1][0])) {
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        shell->last_status = 1;
        return 1;
    }
    if (!is_alphanum(cmd[1], '\0')) {
        write(2, "setenv: Variable name must contain alphanumeric ", 48);
        write(2, "characters.\n", 12);
        shell->last_status = 1;
        return 1;
    }
    return 0;
}

static void update_env_node(shell_t *shell, char **cmd, char *new_line)
{
    node_t *temp = shell->env;
    int len = my_strlen(cmd[1]);

    while (temp) {
        if (my_strncmp(temp->line, cmd[1], len) == 0 &&
            temp->line[len] == '=') {
            free(temp->line);
            temp->line = new_line;
            return;
        }
        temp = temp->next;
    }
    shell->env = add_node(shell->env, new_line);
}

void set_env(char **cmd, shell_t *shell)
{
    char *new_line = NULL;

    if (!cmd[1]) {
        print_env(cmd, shell);
        shell->last_status = 0;
        return;
    }
    if (env_error(cmd, shell))
        return;
    shell->last_status = 0;
    new_line = create_env_line(cmd[1], cmd[2]);
    update_env_node(shell, cmd, new_line);
}
