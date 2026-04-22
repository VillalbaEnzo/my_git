/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** path_handling
*/
#include "utils.h"
#include "mysh.h"
#include "cmd_array.h"

char *skip_env_name(char *path)
{
    while (*path != '=')
        path++;
    path++;
    return path;
}

int find_path(char **envp)
{
    for (int i = 0; envp[i] != NULL; i++) {
        if (!my_strncmp("PATH=", envp[i], 5))
            return i;
    }
    return -1;
}

static char *create_command(int temp_size, const char *path_to_try,
    char *command)
{
    char *temp_cmd = malloc(sizeof(char) * temp_size + 2);

    if (!temp_cmd)
        return NULL;
    temp_cmd[0] = '\0';
    temp_cmd = my_strcat(temp_cmd, path_to_try);
    temp_cmd = my_strcat(temp_cmd, "/");
    temp_cmd = my_strcat(temp_cmd, command);
    return temp_cmd;
}

char *try_paths(char *path_copy, char *command)
{
    char *path_str = my_strdup(strtok(path_copy, ":"));
    char *temp_cmd = NULL;
    int temp_size = 0;

    while (path_str != NULL) {
        temp_size = my_strlen(path_str) + my_strlen(command);
        temp_cmd = create_command(temp_size, path_str, command);
        if (access(temp_cmd, F_OK | X_OK) == -1) {
            free(path_str);
            path_str = my_strdup(strtok(NULL, ":"));
            free(temp_cmd);
        } else {
            free(path_str);
            return temp_cmd;
        }
    }
    return NULL;
}

char *try_default_paths(char *command)
{
    char *temp_cmd = NULL;
    int temp_size = 0;

    for (int i = 0; def_paths[i] != NULL; i++) {
        temp_size = my_strlen(def_paths[i]) + my_strlen(command);
        temp_cmd = create_command(temp_size, def_paths[i], command);
        if (access(temp_cmd, F_OK | X_OK) == -1) {
            free(temp_cmd);
            continue;
        } else
            return temp_cmd;
    }
    return NULL;
}

char *handle_path(char *command, char **envp, char *command_saver)
{
    int path_pos = find_path(envp);
    char *path_copy = NULL;
    char *new_cmd = NULL;
    char *safe_path = NULL;

    if (path_pos == -1)
        new_cmd = try_default_paths(command);
    else {
        path_copy = my_strdup(envp[path_pos]);
        safe_path = path_copy;
        path_copy = skip_env_name(path_copy);
        new_cmd = try_paths(path_copy, command);
        free(safe_path);
    }
    if (new_cmd == NULL) {
        mini_printf(2, "%s: Command not found.\n", command_saver);
        free(command_saver);
        return NULL;
    } else
        return new_cmd;
}
