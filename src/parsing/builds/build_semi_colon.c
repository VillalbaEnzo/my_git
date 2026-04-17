/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** build_semi_colon
*/

#include "as_tree.h"
#include "mysh.h"

struct ast_node *create_semi_colon(struct ast_node *prev_root,
    char **token, int *last_pos)
{
    struct ast_node *new_root = malloc(sizeof(struct ast_node));

    if (!new_root)
        return NULL;
    new_root->type = SEMI_COLON;
    new_root->semic_node = malloc(sizeof(ast_semic_t));
    if (!new_root->semic_node)
        return NULL;
    new_root->semic_node->left = prev_root;
    (*last_pos)++;
    new_root->semic_node->right = get_command(token, last_pos);
    return new_root;
}
