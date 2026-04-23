/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** build_tree
*/

#include "as_tree.h"
#include "utils.h"
#include "mysh.h"
#include "cmd_array.h"

static void free_tokens(char **token)
{
    for (int i = 0; token[i] != NULL; i++)
        free(token[i]);
    free(token);
}

struct ast_node *read_token(struct ast_node *root, char **token, int *last_pos)
{
    if (my_strcmp(token[*last_pos], ";") == 0)
        return create_semi_colon(root, token, last_pos);
    if (my_strcmp(token[*last_pos], "|") == 0)
        return create_pipe(root, token, last_pos);
    if (my_strcmp(token[*last_pos], "&&") == 0)
        return create_and_node(root, token, last_pos);
    if (my_strcmp(token[*last_pos], "||") == 0)
        return create_or_node(root, token, last_pos);
    return root;
}

struct ast_node *build_tree(char **token)
{
    struct ast_node *root = NULL;
    int last_pos = 0;

    if (token == NULL || token[last_pos] == NULL)
        return NULL;
    if (my_strcmp(token[last_pos], "if") == 0)
        root = create_if_node(token, &last_pos);
    else root = get_command(token, &last_pos);
    while (token[last_pos] != NULL)
        root = read_token(root, token, &last_pos);
    free_tokens(token);
    return root;
}
