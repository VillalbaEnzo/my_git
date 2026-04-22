/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** free_semi_colon
*/

#include "mysh.h"
#include "as_tree.h"

void free_semi_colon(ast_semic_t *semic_node)
{
    free_from_root(semic_node->left);
    free_from_root(semic_node->right);
    free(semic_node);
}
