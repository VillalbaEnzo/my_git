/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** find_in_path.c
*/

#include "my.h"

char *find_in_path(char *path, char *cmd)
{
    char *token = NULL;
    char *temp = NULL;
    char *path_copy = my_strdup(path);

    if (!path_copy)
        return NULL;
    token = strtok(path_copy, ":");
    while (token != NULL) {
        temp = malloc(strlen(token) + strlen(cmd) + 2);
        if (!temp)
            return NULL;
        my_strcpy(temp, token);
        my_strcat(temp, "/");
        my_strcat(temp, cmd);
        printf("%s\n", temp);
        free(temp);
        token = strtok(NULL, ":");
    }
    free(path_copy);
    return NULL;
}
