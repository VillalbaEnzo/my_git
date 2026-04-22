/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-42sh-2 [WSL: Ubuntu-24.04]
** File description:
** flow.c
*/

#include "as_tree.h"
#include "mysh.h"
#include "utils.h"
#include "builtin.h"
#include "cmd_array.h"

int exec_while(struct ast_node *node, data_t *data, char **envp)
{
    int ret = 0;

    while (1) {
        ret = traverse_tree(node->while_node->condition, data, envp);
        if (ret != 0)
            break;
        ret = traverse_tree(node->while_node->body, data, envp);
    }
    return 0;
}
