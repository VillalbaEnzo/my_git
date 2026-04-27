/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** changes directory
*/
#include "mysh.h"
#include "utils.h"
#include "builtin.h"

int find_old_pwd(char **envp)
{
    for (int i = 0; envp[i] != NULL; i++) {
        if (!my_strncmp(envp[i], "OLDPWD", 6))
            return i;
    }
    return -1;
}

char *get_old_pwd(char **envp)
{
    int pos = find_old_pwd(envp);
    char *temp_env_var = NULL;
    char *old_pwd = NULL;

    if (pos == -1)
        return NULL;
    temp_env_var = my_strdup(envp[pos]);
    strtok(temp_env_var, "=");
    old_pwd = my_strdup(strtok(NULL, "="));
    free(temp_env_var);
    return old_pwd;
}

args_t *create_setenv_args(char *cwd_keeper, char **envp)
{
    args_t *setenv_args = malloc(sizeof(args_t));

    if (!setenv_args)
        return NULL;
    setenv_args->data = NULL;
    setenv_args->envp = envp;
    setenv_args->args = malloc(sizeof(char *) * 3);
    if (!setenv_args->args)
        return NULL;
    setenv_args->args[0] = "setenv";
    setenv_args->args[1] = "OLDPWD";
    setenv_args->args[2] = cwd_keeper;
    return setenv_args;
}

int change_dir(args_t *args)
{
    char *cwd_keeper = getcwd(NULL, 0);
    args_t *setenv_args = create_setenv_args(cwd_keeper, args->envp);

    if (!my_strcmp(args->args[1], "-"))
        args->args[1] = get_old_pwd(args->envp);
    if (args->args[1] == NULL) {
        mini_printf(2, ": No such file or directory.\n");
        return 1;
    }
    if (chdir(args->args[1]) == -1) {
        mini_printf(2, "%s: %s.\n", args->args[1], strerror(errno));
        return 1;
    }
    set_env(setenv_args);
    add_local_var(args->data->local_vars, strdup("cwd"), getcwd(NULL, 0));
    free(cwd_keeper);
    free(setenv_args->args);
    free(setenv_args);
    return 0;
}
