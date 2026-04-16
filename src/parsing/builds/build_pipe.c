/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** build_pipe
*/

#include "as_tree.h"
#include "mysh.h"

struct ast_node *create_pipe(struct ast_node *root, char **token,
    int *last_pos)
{
    struct ast_node *pipe = malloc(sizeof(struct ast_node));

    if (!pipe)
        return NULL;
    pipe->type = PIPE;
    pipe->pipe_node = malloc(sizeof(ast_pipe_t));
    if (!pipe->pipe_node)
        return NULL;
    if (root->type == SEMI_COLON) {
        pipe->pipe_node->writer = root->semic_node->right;
        root->semic_node->right = pipe;
    } else {
        pipe->pipe_node->writer = root;
        root = pipe;
    }
    (*last_pos)++;
    pipe->pipe_node->reader = get_command(token, last_pos);
    return root;
}
