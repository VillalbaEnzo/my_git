/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** which
*/

#include "mysh.h"
#include "builtin.h"
#include "utils.h"

int find_command(args_t *args, char *cmd_save, int i)
{
    char *temp_cmd = NULL;

    if (check_builtin(args->args[i]) == 1) {
        mini_printf(1, "%s: shell built-in command.\n", args->args[i]);
        free(cmd_save);
        return 0;
    }
    temp_cmd = handle_path(args->args[i], args->envp, cmd_save);
    if (temp_cmd == NULL)
        return 1;
    else {
        mini_printf(1, "%s\n", temp_cmd);
        free(temp_cmd);
        free(cmd_save);
        return 0;
    }
}

int which(args_t *args)
{
    char *cmd_save = NULL;
    int temp_ret = 0;
    int def_ret = 0;

    if (args->args[1] == NULL) {
        mini_printf(2, "which: Too few arguments.\n");
        return 1;
    }
    for (int i = 1; args->args[i] != NULL; i++) {
        cmd_save = my_strdup(args->args[i]);
        temp_ret = find_command(args, cmd_save, i);
        if (temp_ret > def_ret)
            def_ret = temp_ret;
    }
    return def_ret;
}
