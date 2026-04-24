/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-42sh-2 [WSL: Ubuntu-24.04]
** File description:
** build_if.c
*/

#include "as_tree.h"
#include "mysh.h"
#include "utils.h"

struct contexte_s {
    char **tokens;
    int i;
    int start;
};

static int count_condition(char **tokens, int start)
{
    int parenthesis = 0;
    int count = 0;

    for (int i = start; tokens[i]; i++) {
        if (my_strcmp(tokens[i], "(") == 0)
            parenthesis++;
        if (my_strcmp(tokens[i], ")") == 0)
            parenthesis--;
        count++;
        if (parenthesis == 0)
            break;
    }
    return count;
}

static char **extract_if_condition(char **tokens, int *last_pos)
{
    int start = *last_pos;
    int count = 0;
    char **cond_tokens = NULL;

    if (my_strcmp(tokens[start], "(") != 0)
        return NULL;
    count = count_condition(tokens, start);
    if (count < 2) {
        *last_pos = start + count;
        return NULL;
    }
    cond_tokens = malloc(sizeof(char *) * (count - 1));
    if (!cond_tokens)
        return NULL;
    for (int i = 0; i < count - 2; i++)
        cond_tokens[i] = my_strdup(tokens[start + 1 + i]);
    cond_tokens[count - 2] = NULL;
    *last_pos = start + count;
    return cond_tokens;
}

static void handle_branch_verif(int *if_c, int *end_p, int *else_p,
    struct contexte_s *ctx)
{
    char **tokens = ctx->tokens;
    int i = ctx->i;

    if (my_strcmp(tokens[i], "if") == 0 &&
        !(i > ctx->start && my_strcmp(tokens[i - 1], "else") == 0))
        (*if_c)++;
    if (my_strcmp(tokens[i], "endif") == 0)
        (*if_c)--;
    if (*if_c == 0 && *end_p == -1)
        *end_p = i;
    if (my_strcmp(tokens[i], "else") == 0 &&
        *if_c == 1 && *else_p == -1)
        *else_p = i;
}

static void find_branches_pos(char **tokens, int start, int *else_p,
    int *end_p)
{
    int if_count = 1;
    struct contexte_s ctx;

    *else_p = -1;
    *end_p = -1;
    ctx.tokens = tokens;
    ctx.start = start;
    for (int i = start; tokens[i] && *end_p == -1; i++) {
        ctx.i = i;
        handle_branch_verif(&if_count, end_p, else_p, &ctx);
    }
    if (*end_p == -1)
        for (*end_p = start; tokens[*end_p]; (*end_p)++);
}

static char **copy_tokens(char **tokens, int start, int len)
{
    char **new_toks = NULL;

    if (len <= 0)
        return NULL;
    new_toks = malloc(sizeof(char *) * (len + 1));
    if (!new_toks)
        return NULL;
    for (int i = 0; i < len; i++)
        new_toks[i] = my_strdup(tokens[start + i]);
    new_toks[len] = NULL;
    return new_toks;
}

static void extract_branches(char **tokens, int *last_pos,
    char ***then_t, char ***else_t)
{
    int start = *last_pos;
    int else_p = 0;
    int end_p = 0;
    int then_len = 0;

    find_branches_pos(tokens, start, &else_p, &end_p);
    then_len = (else_p != -1) ? (else_p - start) : (end_p - start);
    *then_t = copy_tokens(tokens, start, then_len);
    if (else_p != -1)
        *else_t = copy_tokens(tokens, else_p + 1, end_p - else_p - 1);
    else *else_t = NULL;
    *last_pos = tokens[end_p] ? (end_p + 1) : end_p;
}

struct ast_node *create_if_node(char **token, int *last_pos)
{
    struct ast_node *if_root = malloc(sizeof(struct ast_node));
    char **then_t = NULL;
    char **else_t = NULL;

    if (!if_root)
        return NULL;
    if_root->type = IF;
    if_root->if_node = malloc(sizeof(ast_if_t));
    if (!if_root->if_node) {
        free(if_root);
        return NULL;
    }
    if_root->if_node->else_branch = NULL;
    (*last_pos)++;
    if_root->if_node->condition = build_tree(extract_if_condition(token,
            last_pos));
    if (token[*last_pos] && my_strcmp(token[*last_pos], "then") == 0) {
        (*last_pos)++;
        extract_branches(token, last_pos, &then_t, &else_t);
        if_root->if_node->then_branch = build_tree(then_t);
        if (then_t)
            if_root->if_node->then_branch = build_tree(then_t);
        if (else_t)
            if_root->if_node->else_branch = build_tree(else_t);
    } else if_root->if_node->then_branch = get_command(token, last_pos);
    return if_root;
}
