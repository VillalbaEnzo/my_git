/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-42sh-2 [WSL: Ubuntu-24.04]
** File description:
** free_if.c
*/

#include "mysh.h"
#include "as_tree.h"

void free_if(ast_if_t *if_node)
{
    free_from_root(if_node->condition);
    free_from_root(if_node->else_branch);
    free_from_root(if_node->then_branch);
    free(if_node);
}
