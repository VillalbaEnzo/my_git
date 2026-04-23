/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** check_builtin
*/

#include "mysh.h"
#include "builtin.h"
#include "utils.h"

int check_builtin(char *command)
{
    for (int i = 0; i < NB_BUILTIN; i++) {
        if (my_strcmp(command, bt_array[i].builtin_name) == 0)
            return 1;
    }
    return 0;
}
