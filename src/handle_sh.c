/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** sh.c
*/

#include "my.h"

int handle_sh(char *line, char **env)
{
    size_t len = 0;
    ssize_t ret;
    char *cmd;

    while (1) {
        mini_printf("$> ");
        ret = getline(&line, &len, stdin);
        if (ret == -1)
            break;
        cmd = clear_line(line);
        printf("%s", cmd);
        if (my_strcmp(cmd, "exit") == 0)
            break;
    }
    free(line);
    return 0;
}
