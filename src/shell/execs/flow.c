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

static int int_operation_condition(int left, int right, char *op)
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

static int num_condition(char **args)
{
    int left = 0;
    int right = 0;
    char *op = NULL;

    if (!args[1])
        return atoi(args[0]) != 0;
    if (args[2]) {
        left = atoi(args[0]);
        right = atoi(args[2]);
        op = args[1];
        return int_operation_condition(left, right, op);
    }
    return 0;
}

static int str_condition(char **args)
{
    if (my_strcmp(args[1], "==") == 0)
        return my_strcmp(args[0], args[2]) == 0;
    if (my_strcmp(args[1], "!=") == 0)
        return my_strcmp(args[0], args[2]) != 0;
    return 0;
}

static int handle_condition(char **args)
{
    if (!args || !args[0])
        return 0;
    if (args[2] && is_numeric(args[0]) && is_numeric(args[2]))
        return num_condition(args);
    return str_condition(args);
}

int exec_if(struct ast_node *node, data_t *data, char **envp)
{
    char **cond_args = NULL;

    if (!node || !node->if_node || !node->if_node->condition)
        return 1;
    if (node->if_node->condition->type != COMMAND ||
        !node->if_node->condition->cmd_node) {
        mini_printf(2, "if: Expression Syntax.\n");
        return 1;
    }
    if (args_exp(node->if_node->condition->cmd_node, data) == 1)
        return 1;
    cond_args = node->if_node->condition->cmd_node->arguments;
    if (handle_condition(cond_args))
        return traverse_tree(node->if_node->then_branch, data, envp);
    else if (node->if_node->else_branch)
        return traverse_tree(node->if_node->else_branch, data, envp);
    return 0;
}
