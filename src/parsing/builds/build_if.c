/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-42sh-2 [WSL: Ubuntu-24.04]
** File description:
** build_if.c
*/

#include "as_tree.h"
#include "mysh.h"
#include "utils.h"

static char **extract_if_condition(char **tokens, int *last_pos)
{
    int parenthesis = 0;
    int start = *last_pos;
    int count = 0;
    char **cond_tokens = NULL;

    if (my_strcmp(tokens[start], "(") != 0) return NULL;

    for (int i = start; tokens[i]; i++) {
        if (my_strcmp(tokens[i], "(") == 0) parenthesis++;
        if (my_strcmp(tokens[i], ")") == 0) parenthesis--;
        count++;
        if (parenthesis == 0) break;
    }

    cond_tokens = malloc(sizeof(char *) * (count - 1));
    for (int i = 0; i < count - 2; i++)
        cond_tokens[i] = my_strdup(tokens[start + 1 + i]);
    cond_tokens[count - 2] = NULL;
    *last_pos = start + count;
    return cond_tokens;
}

static char **extract_if_body(char **tokens, int *last_pos)
{
    int if_count = 1;
    int start = *last_pos;
    int count = 0;
    char **body_tokens = NULL;

    for (int i = start; tokens[i]; i++) {
        if (my_strcmp(tokens[i], "if") == 0) if_count++;
        if (my_strcmp(tokens[i], "endif") == 0) if_count--;
        count++;
        if (if_count == 0) break;
    }

    body_tokens = malloc(sizeof(char *) * count);
    for (int i = 0; i < count - 1; i++)
        body_tokens[i] = my_strdup(tokens[start + i]);
    body_tokens[count - 1] = NULL;
    *last_pos = start + count;
    return body_tokens;
}

struct ast_node *create_if_node(char **token, int *last_pos)
{
    struct ast_node *if_root = malloc(sizeof(struct ast_node));

    if (!if_root)
        return NULL;
    if_root->type = IF_NODE;
    if_root->if_node = malloc(sizeof(ast_if_t));
    if_root->if_node->else_branch = NULL;
    (*last_pos)++;
    if_root->if_node->condition = build_tree(extract_if_condition(token,
        last_pos));
    if (token[*last_pos] && my_strcmp(token[*last_pos], "then") == 0) {
        (*last_pos)++;
        if_root->if_node->then_branch = build_tree(extract_if_body(token,
            last_pos));
    } else if_root->if_node->then_branch = get_command(token, last_pos);
    return if_root;
}
