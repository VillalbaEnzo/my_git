/*
** EPITECH PROJECT, 2026
** minishell2 [WSL: Ubuntu]
** File description:
** error_handling
*/

#include "mysh.h"
#include "as_tree.h"
#include "utils.h"

bool check_command(ast_cmd_t *cmd_node, node_type_t prev_node_type)
{
    if (cmd_node->arguments[0] == NULL && prev_node_type != SEMI_COLON
        && prev_node_type != COMMAND)
        return false;
    for (int i = 0; i < cmd_node->redir_count; i++) {
        if (cmd_node->redirections[i].filename == NULL) {
            mini_printf(2, "Missing name for redirect.\n");
            return false;
        }
    }
    return true;
}

bool pre_check_tree(struct ast_node *root, bool is_first_node,
    node_type_t prev_node_type)
{
    if (root == NULL)
        return is_first_node;
    switch (root->type) {
        case SEMI_COLON:
            if (!pre_check_tree(root->semic_node->left, false, SEMI_COLON))
                return false;
            return pre_check_tree(root->semic_node->right, false, SEMI_COLON);
        case PIPE:
            return check_pipe(root);
        case COMMAND:
            return check_command(root->cmd_node, prev_node_type);
        case AND:
            return true;
        case XOR:
            return true;
        default:
            return false;
    }
}
