/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** build_command
*/

#include "as_tree.h"
#include "mysh.h"
#include "cmd_array.h"
#include "utils.h"

static int count_redirections(char **token, int last_pos)
{
    int count = 0;

    for (int i = last_pos; token[i] != NULL && is_symbol(token[i]) != 1; i++) {
        if (is_operator(token[i]))
            count++;
    }
    return count;
}

static redir_type_t get_redir_type(char *token)
{
    for (int i = 0; operators[i] != NULL; i++) {
        if (my_strcmp(token, operators[i]) == 0)
            return i;
    }
    return NOT_R;
}

static redir_t *get_redirections(char **token, int *last_pos, int *redir_count)
{
    redir_t *redir_array = NULL;
    int redir_pos = 0;

    if (token[*last_pos] == NULL || is_symbol(token[*last_pos]))
        return NULL;
    (*redir_count) = count_redirections(token, (*last_pos));
    redir_array = malloc(sizeof(redir_t) * (*redir_count));
    if (!redir_array)
        return NULL;
    for (; token[(*last_pos)] != NULL &&
        is_symbol(token[(*last_pos)]) != 1; (*last_pos)++) {
        if (is_operator(token[*last_pos])) {
            redir_array[redir_pos].type = get_redir_type(token[*last_pos]);
            redir_array[redir_pos].filename = my_strdup(token[*last_pos + 1]);
            redir_pos++;
        }
    }
    return redir_array;
}

static char **get_arguments(char **token, int *last_pos)
{
    int size = count_args(token, *last_pos);
    char **args = malloc(sizeof(char *) * (size + 1));
    int arg_count = 0;

    if (!args)
        return NULL;
    args[size] = NULL;
    for (; token[*last_pos] != NULL && is_operator(token[*last_pos])
        != 1 && is_symbol(token[*last_pos]) != 1; (*last_pos)++) {
        args[arg_count] = my_strdup(token[*last_pos]);
        arg_count++;
    }
    return args;
}

struct ast_node *get_command(char **token, int *last_pos)
{
    struct ast_node *cmd_node = malloc(sizeof(struct ast_node));

    if (!cmd_node) {
        free(cmd_node);
        return NULL;
    }
    cmd_node->type = COMMAND;
    cmd_node->cmd_node = malloc(sizeof(ast_cmd_t));
    if (!cmd_node->cmd_node)
        return NULL;
    cmd_node->cmd_node->arguments = get_arguments(token, last_pos);
    if (!cmd_node->cmd_node->arguments)
        return NULL;
    cmd_node->cmd_node->redir_count = 0;
    cmd_node->cmd_node->redirections = get_redirections(token, last_pos,
        &(cmd_node->cmd_node->redir_count));
    return cmd_node;
}
