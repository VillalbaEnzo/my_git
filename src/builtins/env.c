/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** environment listing
*/
#include "mysh.h"
#include "utils.h"
#include "builtin.h"

int env(args_t *args)
{
    for (int i = 0; args->envp[i] != NULL; i++) {
        mini_printf(1, "%s\n", args->envp[i]);
    }
    return 0;
}
