/*
** EPITECH PROJECT, 2026
** robotfactory
** File description:
** my_str_to_word_array
*/

#include "op.h"

size_t count_tokens(char *src, char delim)
{
    size_t count = 0;
    bool is_quoted = false;

    for (int i = 0; src[i] != '\0'; i++) {
        if (src[i] == '"')
            is_quoted = !is_quoted;
        if (src[i] == delim && is_quoted == false)
            count++;
    }
    count++;
    return count;
}

size_t get_token_size(char *src, char delim, int last_tok_pos)
{
    size_t size = 0;
    bool is_quoted = false;

    for (int i = last_tok_pos; src[i] != '\0'; i++) {
        if (src[i] == '"') {
            is_quoted = !is_quoted;
            continue;
        }
        if (src[i] == delim && is_quoted == false)
            break;
        size++;
    }
    return size;
}

char *get_token(char *src, char delim, int *last_tok_pos)
{
    char *token = NULL;
    size_t tok_size = get_token_size(src, delim, *last_tok_pos);

    token = malloc(sizeof(char) * (tok_size + 1));
    if (!token)
        return NULL;
    if (src[*last_tok_pos] == '"')
        (*last_tok_pos)++;
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
 * @warning Strings in double quotes are considered a single token
 * @warning If such strings are in tokens, double quotes will be removed from
 * the token
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
        tokens[i] = get_token(src, delim, &last_tok_pos);
        if (tokens[i] == NULL)
            return NULL;
    }
    tokens[array_size] = NULL;
    return tokens;
}
