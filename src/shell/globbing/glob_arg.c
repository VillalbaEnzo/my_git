/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** glob_arg
*/

#include "mysh.h"

char **glob_arg(char **args)
{
    glob_t glo_buff;

    glo_buff.gl_offs = 1;
    if (args[1] == NULL)
        return args;
    if (glob(args[1], GLOB_DOOFFS | GLOB_NOCHECK | GLOB_TILDE, NULL,
            &glo_buff) != 0)
        return NULL;
    for (int i = 2; args[i] != NULL; i++) {
        if (glob(args[i], GLOB_DOOFFS | GLOB_NOCHECK | GLOB_TILDE |
                GLOB_APPEND, NULL, &glo_buff) != 0)
            return NULL;
    }
    glo_buff.gl_pathv[0] = strdup(args[0]);
    free_array((void **)args);
    return glo_buff.gl_pathv;
}
