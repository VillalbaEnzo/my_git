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

static int operation_condition(int left, int right, char *op)
{
    if (my_strcmp(op, "<") == 0)
        return left < right;
    if (my_strcmp(op, ">") == 0)
        return left > right;
    if (my_strcmp(op, "==") == 0)
        return left == right;
    if (my_strcmp(op, "!=") == 0)
        return left != right;
    if (my_strcmp(op, "<=") == 0)
        return left <= right;
    if (my_strcmp(op, ">=") == 0)
        return left >= right;
    return 0;
}

static int simple_condition(char **args)
{
    int left = 0;
    int right = 0;
    char *op = NULL;

    if (!args || !args[0])
        return 0;
    if (args[1] == NULL)
        return atoi(args[0]) != 0;
    if (args[2] != NULL) {
        left = atoi(args[0]);
        right = atoi(args[2]);
        op = args[1];
        return operation_condition(left, right, op);
    }
    return 0;
}

int exec_if(struct ast_node *node, data_t *data, char **envp)
{
    char **cond_args = NULL;

    if (!node || !node->if_node || !node->if_node->condition)
        return 1;
    cond_args = node->if_node->condition->cmd_node->arguments;
    if (simple_condition(cond_args))
        return traverse_tree(node->if_node->then_branch, data, envp);
    else if (node->if_node->else_branch)
        return traverse_tree(node->if_node->else_branch, data, envp);
    return 0;
}
