/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** free_pipe
*/

#include "as_tree.h"
#include "mysh.h"

void free_pipe(ast_pipe_t *pipe_node)
{
    free_from_root(pipe_node->writer);
    free_from_root(pipe_node->reader);
    free(pipe_node);
}
