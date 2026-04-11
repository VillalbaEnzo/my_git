/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** build_logic_op
*/

#include "as_tree.h"
#include "mysh.h"

struct ast_node *create_and_node(struct ast_node *root, char **token,
    int *last_pos)
{
    struct ast_node *and = malloc(sizeof(struct ast_node));

    if (!and)
        return NULL;
    and->type = AND;
    and->and_node = malloc(sizeof(ast_and_t));
    if (!and->and_node)
        return NULL;
    if (root->type == SEMI_COLON) {
        and->and_node->cmd1 = root->semic_node->right;
        root->semic_node->right = and;
    } else {
        and->and_node->cmd1 = root;
        root = and;
    }
    (*last_pos)++;
    and->and_node->cmd2 = get_command(token, last_pos);
    return root;
}

struct ast_node *create_xor_node(struct ast_node *root, char **token,
    int *last_pos)
{
    struct ast_node *xor = malloc(sizeof(struct ast_node));

    if (!xor)
        return NULL;
    xor->type = XOR;
    xor->xor_node = malloc(sizeof(ast_xor_t));
    if (!xor->xor_node)
        return NULL;
    if (root->type == SEMI_COLON) {
        xor->xor_node->cmd1 = root->semic_node->right;
        root->semic_node->right = xor;
    } else {
        xor->xor_node->cmd1 = root;
        root = xor;
    }
    (*last_pos)++;
    xor->xor_node->cmd2 = get_command(token, last_pos);
    return root;
}
