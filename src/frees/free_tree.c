/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** free_tree
*/
#include "mysh.h"
#include "as_tree.h"

void free_array(void **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

static void free_redirections(ast_cmd_t *node)
{
    for (int i = 0; i < node->redir_count; i++) {
        free((void *)node->redirections[i].filename);
    }
    free(node->redirections);
}

static void free_command(ast_cmd_t *cmd_node)
{
    free_array((void **)cmd_node->arguments);
    if (cmd_node->redirections)
        free_redirections(cmd_node);
    free(cmd_node);
}

static void free_continuation(struct ast_node *root)
{
    switch (root->type) {
        case XOR:
            free_or(root->or_node);
            break;
        case IF:
            free_if(root->if_node);
            break;
        default:
            break;
    }
}

void free_from_root(struct ast_node *root)
{
    if (!root)
        return;
    switch (root->type) {
        case COMMAND:
            free_command(root->cmd_node);
            break;
        case PIPE:
            free_pipe(root->pipe_node);
            break;
        case SEMI_COLON:
            free_semi_colon(root->semic_node);
            break;
        case AND:
            free_and(root->and_node);
            break;
        default:
            free_continuation(root);
            break;
    }
    free(root);
}

static void free_local_var(local_var_t *local_var)
{
    local_var_t *temp;

    while (local_var) {
        temp = local_var->next;
        if (local_var->name)
            free(local_var->name);
        if (local_var->value)
            free(local_var->value);
        free(local_var);
        local_var = temp;
    }
}

void free_data(data_t *data)
{
    if (!data)
        return;
    if (data->root)
        free_from_root(data->root);
    if (data->local_vars) {
        free_local_var(data->local_vars);
        data->local_vars = NULL;
    }
    free(data);
}
