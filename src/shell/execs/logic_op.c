/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** xor
*/

#include "as_tree.h"
#include "mysh.h"

int exec_and(struct ast_node *root, data_t *data, char **envp)
{
    int ret = 0;

    ret = traverse_tree(root->and_node->cmd1, data, envp);
    if (ret != 0)
        return ret;
    else
        return traverse_tree(root->and_node->cmd2, data, envp);
}

int exec_xor(struct ast_node *root, data_t *data, char **envp)
{
    int ret = 0;

    ret = traverse_tree(root->xor_node->cmd1, data, envp);
    if (ret != 0)
        return traverse_tree(root->xor_node->cmd2, data, envp);
    else
        return ret;
}
