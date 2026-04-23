/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-42sh-2 [WSL: Ubuntu-24.04]
** File description:
** build_while.c
*/

// #include "as_tree.h"
// #include "mysh.h"
// #include "utils.h"

// static char **extract_condition_tokens(char **tokens, int *last_pos)
// {
//     int parenthesis = 0;
//     int start = *last_pos;
//     int count = 0;
//     char **cond_tokens = NULL;

//     if (my_strcmp(tokens[start], "(") != 0) {
//         mini_printf(2, "while: Syntax error.\n");
//         return NULL;
//     }
//     for (int i = start; tokens[i]; i++) {
//         if (my_strcmp(tokens[i], "(") == 0)
//             parenthesis++;
//         if (my_strcmp(tokens[i], ")") == 0)
//             parenthesis--;
//         count++;
//         if (parenthesis == 0)
//             break;
//     }
//     if (parenthesis != 0) {
//         mini_printf(2, "Too many ('s.\n");
//         return NULL;
//     }
//     cond_tokens = malloc(sizeof(char *) * (count - 1));
//     if (!cond_tokens)
//         return NULL;
//     for (int i = 0; i < count - 2; i++)
//         cond_tokens[i] = my_strdup(tokens[start + 1 + i]);
//     cond_tokens[count - 2] = NULL;
//     *last_pos = start + count;
//     return cond_tokens;
// }

// char **extract_body_tokens(char **tokens, int *last_pos)
// {
//     int end_count = 1;
//     int start = *last_pos;
//     int count = 0;
//     char **body_tokens = NULL;

//     for (int i = start; tokens[i]; i++) {
//         if (my_strcmp(tokens[i], "while") == 0 || my_strcmp(tokens[i],
//                 "foreach") == 0)
//             end_count++;
//         if (my_strcmp(tokens[i], "end") == 0)
//             end_count--;
//         count++;
//         if (end_count == 0)
//             break;
//     }
//     if (end_count != 0) {
//         mini_printf(2, "while: end not found.\n");
//         return NULL;
//     }
//     body_tokens = malloc(sizeof(char *) * count);
//     if (!body_tokens)
//         return NULL;
//     for (int i = 0; i < count - 1; i++)
//         body_tokens[i] = my_strdup(tokens[start + i]);
//     body_tokens[count - 1] = NULL;
//     *last_pos = start + count;
//     return body_tokens;
// }

// struct ast_node *create_while_node(char **token, int *last_pos)
// {
//     char **cond_tokens = NULL;
//     char **body_tokens = NULL;
//     struct ast_node *while_root = malloc(sizeof(struct ast_node));

//     if (!while_root)
//         return NULL;
//     while_root->type = WHILE_NODE;
//     while_root->while_node = malloc(sizeof(ast_while_t));
//     (*last_pos)++;
//     cond_tokens = extract_condition_tokens(token, last_pos);
//     while_root->while_node->condition = build_tree(cond_tokens);
//     body_tokens = extract_body_tokens(token, last_pos);
//     while_root->while_node->body = build_tree(body_tokens);
//     return while_root;
// }
