/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** where
*/

#include "mysh.h"
#include "builtin.h"
#include "utils.h"
#include "cmd_array.h"

static char *create_name(int temp_size, const char *path_to_try,
    char *command)
{
    char *temp_name = malloc(sizeof(char) * temp_size + 2);

    if (!temp_name)
        return NULL;
    temp_name[0] = '\0';
    temp_name = my_strcat(temp_name, path_to_try);
    temp_name = my_strcat(temp_name, "/");
    temp_name = my_strcat(temp_name, command);
    return temp_name;
}

static void free_tokens(char **tok_arr)
{
    for (int i = 0; tok_arr[i] != NULL; i++)
        free(tok_arr[i]);
    free(tok_arr);
}

int locate_in_paths(char **path_arr, char *cmd)
{
    int temp_size = 0;
    int ret = 1;
    char *tester = NULL;

    for (int i = 0; path_arr[i] != NULL; i++) {
        temp_size = my_strlen(path_arr[i]) + my_strlen(cmd);
        tester = create_name(temp_size, path_arr[i], cmd);
        if (access(tester, F_OK | X_OK) == 0) {
            mini_printf(1, "%s\n", tester);
            ret = 0;
        }
        free(tester);
    }
    return ret;
}

int get_entries_no_path(char *cmd, bool is_builtin)
{
    int ret = locate_in_paths((char **)def_paths, cmd);

    return (ret && !is_builtin);
}

int get_entries(char *cmd, char **envp, bool is_builtin)
{
    int path_pos = find_path(envp);
    char **paths = NULL;
    char *path_str = NULL;
    int ret = 0;

    if (path_pos == -1)
        return get_entries_no_path(cmd, is_builtin);
    else {
        path_str = envp[path_pos];
        path_str = skip_env_name(path_str);
        paths = str_to_token_array_delim(path_str, ':');
        if (paths == NULL)
            return 1;
        ret = locate_in_paths(paths, cmd);
    }
    free_tokens(paths);
    return (ret && !is_builtin);
}

int where(args_t *args)
{
    int temp_ret = 0;
    int def_ret = 0;
    bool is_builtin = false;

    if (args->args[1] == NULL) {
        mini_printf(2, "where: Too few arguments.\n");
        return 1;
    }
    for (int i = 1; args->args[i] != NULL; i++) {
        if (check_builtin(args->args[i]) == 1) {
            mini_printf(1, "%s: shell built-in command.\n", args->args[i]);
            is_builtin = true;
        }
        temp_ret = get_entries(args->args[i], args->envp, is_builtin);
        if (temp_ret > def_ret)
            def_ret = temp_ret;
    }
    return def_ret;
}
