/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** removes env variable
*/
#include "mysh.h"
#include "utils.h"
#include "builtin.h"

int find_target(char *value, char **envp)
{
    int value_size = my_strlen(value);

    for (int i = 0; envp[i] != NULL; i++) {
        if (!my_strncmp(envp[i], value, value_size))
            return i;
    }
    return -1;
}

int array_size(char **envp)
{
    int count = 0;

    for (int i = 0; envp[i] != NULL; i++)
        count++;
    return count;
}

char **del_value(int value_pos, char **envp)
{
    for (int i = value_pos; envp[i] != NULL; i++)
        envp[i] = envp[i + 1];
    return envp;
}

int unset_env(args_t *args)
{
    int value_pos = 0;

    if (!args->args[1]) {
        mini_printf(2, "unsetenv: Too few arguments.\n");
        return 1;
    }
    value_pos = find_target(args->args[1], args->envp);
    if (value_pos == -1)
        return 0;
    args->envp = del_value(value_pos, args->envp);
    return 0;
}
