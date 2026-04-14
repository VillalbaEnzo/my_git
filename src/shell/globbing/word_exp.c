/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** word_exp
*/

#include "mysh.h"

int glob_args(ast_cmd_t *cmd_node)
{
    wordexp_t exp;

    exp.we_offs = 1;
    if (cmd_node->arguments[1] == NULL)
        return 0;
    if (wordexp(cmd_node->arguments[1], &exp, WRDE_DOOFFS | WRDE_SHOWERR) != 0)
        return 1;
    for (int i = 2; cmd_node->arguments[i] != NULL; i++) {
        if (wordexp(cmd_node->arguments[i], &exp, WRDE_DOOFFS |
                WRDE_APPEND | WRDE_SHOWERR) != 0)
            return 1;
    }
    exp.we_wordv[0] = strdup(cmd_node->arguments[0]);
    free_array((void **)cmd_node->arguments);
    cmd_node->arguments = exp.we_wordv;
    return 0;
}
