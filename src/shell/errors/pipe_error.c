/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** pipe_error
*/

#include "mysh.h"
#include "utils.h"

bool check_pipe(struct ast_node *root)
{
    if (!pre_check_tree(root->pipe_node->writer, false, PIPE) ||
        !pre_check_tree(root->pipe_node->reader, false, PIPE)) {
        mini_printf(2, "Invalid null command.\n");
        return false;
    }
    return true;
}
