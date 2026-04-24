/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** displays prompt
*/
#include "mysh.h"
#include "utils.h"

char *get_cwd_path(void)
{
    char *path = NULL;

    path = getcwd(path, 0);
    return path;
}

void display_prompt(void)
{
    char *cwd_path = get_cwd_path();

    mini_printf(1, "%s>$ ", cwd_path);
    free(cwd_path);
}
