/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-42sh-2 [WSL: Ubuntu-24.04]
** File description:
** build_while.c
*/

#include "as_tree.h"
#include "mysh.h"
#include "utils.h"

static int get_condition_len(char *token, int *count)
{
    int parenthesis = 0;

    if (my_strcmp(token, "(") == 0)
        parenthesis++;
    if (my_strcmp(token, ")") == 0) {
        parenthesis--;
        if (parenthesis == 0) {
            *(count)++;
            return 1;
        }
    }
    *(count)++;
    return 0;
}

static char **extract_condition_tokens(char **tokens, int *last_pos)
{
    int start = *last_pos;
    int count = 0;
    char **cond_tokens = NULL;

    for (int i = start; tokens[i]; i++) {
        if (get_condition_len(tokens[i], &count))
            break;
    }
    cond_tokens = malloc(sizeof(char *) * (count + 1));
    if (!cond_tokens)
        return NULL;
    for (int i = 0; i < count; i++)
        cond_tokens[i] = my_strdup(tokens[start + i]);
    cond_tokens[count] = NULL;
    *last_pos = start + count;
    return cond_tokens;
}

static int get_body_len(char *token, int *count)
{
    int end = 1;

    if (my_strcmp(token, "while") == 0 || my_strcmp(token, "foreach") == 0)
        end++;
    if (my_strcmp(token, "end")) {
        end--;
        if (end == 0)
            return 1;
    }
    (*count)++;
    return 0;
}

char **extract_body_tokens(char **tokens, int *last_pos)
{
    int start = *last_pos;
    char **body_tokens = NULL;
    int count = 0;

    for (int i = start; tokens[i]; i++)
        get_body_len(tokens[i], &count);
    body_tokens = malloc(sizeof(char *) * (count + 1));
    if (!body_tokens)
        return NULL;
    for (int i = 0; i < count; i++)
        body_tokens[i] = my_strdup(tokens[start + i]);
    body_tokens[count] = NULL;
    *last_pos = start + count;
    return body_tokens;
}

struct ast_node *create_while_node(char **token, int *last_pos)
{
    char **cond_tokens = NULL;
    char **body_tokens = NULL;
    struct ast_node *while_root = malloc(sizeof(struct ast_node));

    if (!while_root)
        return NULL;
    while_root->type = WHILE_NODE;
    while_root->while_node = malloc(sizeof(ast_while_t));
    (*last_pos)++;
    cond_tokens = extract_condition_tokens(token, last_pos);
    while_root->while_node->condition = build_tree(cond_tokens);
    body_tokens = extract_body_tokens(token, last_pos);
    while_root->while_node->body = build_tree(body_tokens);
    (*last_pos)++;
    return while_root;
}
