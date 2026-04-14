/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** set env variable
*/
#include "mysh.h"
#include "builtin.h"
#include "utils.h"

static int environ_size(char **envp)
{
    int count = 0;

    for (int i = 0; envp[i] != NULL; i++)
        count++;
    return count;
}

static int check_name(char *name)
{
    if (!((64 < name[0] && name[0] < 91) || (96 < name[0] && name[0] < 123)))
        return -2;
    for (int i = 0; name[i] != '\0'; i++) {
        if (name[i] == '=')
            return -1;
    }
    return 0;
}

static int find_target(char *name, char **envp)
{
    int target_size = my_strlen(name);

    for (int i = 0; envp[i] != NULL; i++) {
        if (!my_strncmp(name, envp[i], target_size))
            return i;
    }
    return -1;
}

int add_var(char *name, char *value, char **envp)
{
    int size = environ_size(envp);
    char *new_var = NULL;
    int var_size = my_strlen(name) + my_strlen(value) + 1;

    new_var = malloc(sizeof(char) * var_size + 1);
    if (!new_var)
        return 1;
    new_var[0] = '\0';
    new_var = my_strcat(new_var, name);
    new_var = my_strcat(new_var, "=");
    new_var = my_strcat(new_var, value);
    envp[size] = new_var;
    envp[size + 1] = NULL;
    return 0;
}

int chg_var(char *name, char *value, int var_pos, char **envp)
{
    int var_size = my_strlen(name) + my_strlen(value) + 1;
    char *new_var = malloc(sizeof(char) * (var_size + 1));

    if (!new_var)
        return 1;
    new_var[0] = '\0';
    new_var = my_strcat(new_var, name);
    new_var = my_strcat(new_var, "=");
    new_var = my_strcat(new_var, value);
    envp[var_pos] = new_var;
    return 0;
}

int set_env(args_t *args)
{
    int vpos = 0;

    if (!args->args[1])
        return env(&((args_t){NULL, args->envp, NULL}));
    switch (check_name(args->args[1])) {
        case -1:
            mini_printf(2, "setenv: Variable name must "
                "contain alphanumeric characters.\n");
            return 1;
        case -2:
            mini_printf(2, "setenv: Variable name must "
                "begin with a letter.\n");
            return 1;
        default:
            vpos = find_target(args->args[1], args->envp);
            if (vpos == -1)
                return add_var(args->args[1], args->args[2], args->envp);
            else
                return chg_var(args->args[1], args->args[2], vpos, args->envp);
    }
}
