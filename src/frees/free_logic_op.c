/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** free_logic_op
*/

#include "mysh.h"
#include "as_tree.h"

void free_and(ast_and_t *and_node)
{
    free_from_root(and_node->cmd1);
    free_from_root(and_node->cmd2);
    free(and_node);
}

void free_or(ast_or_t *or_node)
{
    free_from_root(or_node->cmd1);
    free_from_root(or_node->cmd2);
    free(or_node);
}
