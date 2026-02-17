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

void set_env(char **cmd, shell_t *shell)
{
    node_t *temp = shell->env;
    char *new_line = NULL;

    if (!cmd[1]) {
        print_env(cmd, shell);
        return;
    }
    new_line = create_env_line(cmd[1], cmd[2]);
    while (temp) {
        if (my_strncmp(temp->line, cmd[1], my_strlen(cmd[1])) == 0 &&
            temp->line[my_strlen(cmd[1])] == '=') {
            free(temp->line);
            temp->line = new_line;
            return;
        }
        temp = temp->next;
    }
    shell->env = add_node(shell->env, new_line);
}
