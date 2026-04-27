/*
** EPITECH PROJECT, 2026
** robotfactory
** File description:
** my_str_to_word_array
*/

#include "mysh.h"

size_t count_tokens(char *src, char delim)
{
    size_t count = 0;
    int quote = 0;

    for (int i = 0; src[i] != '\0'; i++) {
        if ((src[i] == '"' || src[i] == '\'' || src[i] == '`') && quote == 0) {
            quote = src[i];
            continue;
        }
        if (src[i] == quote) {
            quote = 0;
            continue;
        }
        if (src[i] == delim && quote == 0)
            count++;
    }
    count++;
    return count;
}

size_t get_token_size(char *src, char delim, int last_tok_pos)
{
    size_t size = 0;
    int quote = 0;

    for (int i = last_tok_pos; src[i] != '\0'; i++) {
        if ((src[i] == '"' || src[i] == '\'' || src[i] == '`') && quote == 0) {
            quote = src[i];
            size++;
            continue;
        }
        if (src[i] == quote) {
            quote = 0;
            size++;
            continue;
        }
        if (src[i] == delim && quote == 0)
            break;
        size++;
    }
    return size;
}

char *get_tokens(char *src, char delim, int *last_tok_pos)
{
    char *token = NULL;
    size_t tok_size = get_token_size(src, delim, *last_tok_pos);

    token = malloc(sizeof(char) * (tok_size + 1));
    if (!token)
        return NULL;
    for (size_t i = 0; i < tok_size; i++) {
        token[i] = src[*last_tok_pos];
        (*last_tok_pos)++;
    }
    token[tok_size] = '\0';
    (*last_tok_pos)++;
    return token;
}

/**
 * Separate a string into tokens based off delimiter
 * @param src source string to split
 * @param delim separator between tokens
 * @return array of allocated individual tokens, NULL if error
 * @warning Quoted strings are considered a unique token
 * @warning So are strings in between backticks (command substitution purposes)
 */
char **str_to_token_array_delim(char *src, char delim)
{
    size_t array_size = 0;
    char **tokens = 0;
    int last_tok_pos = 0;

    if (!src)
        return NULL;
    array_size = count_tokens(src, delim);
    if (array_size == 0)
        return NULL;
    tokens = malloc(sizeof(char *) * (array_size + 1));
    for (size_t i = 0; i < array_size; i++) {
        tokens[i] = get_tokens(src, delim, &last_tok_pos);
        if (tokens[i] == NULL)
            return NULL;
    }
    tokens[array_size] = NULL;
    return tokens;
}
