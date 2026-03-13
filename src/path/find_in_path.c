/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** find_in_path.c
*/

#include "my.h"

static char *path_build(char *token, char *cmd)
{
    char *temp = malloc(my_strlen(token) + my_strlen(cmd) + 2);

    if (!temp)
        return NULL;
    my_strcpy(temp, token);
    my_strcat(temp, "/");
    my_strcat(temp, cmd);
    return temp;
}

static int check_access(char *path_cmd)
{
    if (access(path_cmd, F_OK | X_OK) == 0)
        return 1;
    return 0;
}

char *find_in_path(char *path, char *cmd)
{
    char *token = NULL;
    char *temp = NULL;
    char *path_copy = my_strdup(path);

    if (!path_copy)
        return NULL;
    token = strtok(path_copy, ":");
    while (token != NULL) {
        temp = path_build(token, cmd);
        if (check_access(temp)) {
            free(path_copy);
            return temp;
        }
        free(temp);
        token = strtok(NULL, ":");
    }
    free(path_copy);
    return NULL;
}
