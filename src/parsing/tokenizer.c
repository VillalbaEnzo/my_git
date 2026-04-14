/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** tokenizer
*/
#include "mysh.h"
#include "utils.h"

static void skip_string(char *input, int *i, int *count)
{
    (*i) += 2;
    while (input[*i - 1] != '"') {
        (*i)++;
        if (input[*i + 1] == '\0')
            return;
    }
    (*count)++;
}

static int count_tokens(char *input)
{
    int count = 0;

    if (!input)
        return count;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == ' ')
            count++;
        if (input[i] == '"')
            skip_string(input, &i, &count);
    }
    count++;
    return count;
}

static size_t get_full_size(char *input)
{
    size_t size = 0;

    for (int count = 1; input[count] != '"' && input[count] != '\0'; count++)
        size++;
    return size;
}

static size_t get_token_size(char *input)
{
    size_t size = 0;

    if (input[size] == '"')
        return get_full_size(input);
    for (; input[size] != ' ' && input[size] != '\0'; size++);
    return size;
}

char *go_to_next(char *input, int token_size, bool is_quoted)
{
    int count = 0;

    while (count < token_size) {
        input++;
        count++;
    }
    input++;
    if (is_quoted)
        input += 2;
    return input;
}

char *get_token(char *input, bool *is_quoted)
{
    size_t token_size = get_token_size(input);
    char *token = malloc(sizeof(char) * (token_size + 1));

    token[token_size] = '\0';
    if (*input == '"') {
        input++;
        (*is_quoted) = true;
    }
    token = my_strncpy(token, input, token_size);
    return token;
}

char **tokenizer(char *input)
{
    int size = count_tokens(input);
    char **tokens = NULL;
    char *input_save = input;
    bool is_quoted = false;

    if (!input)
        return NULL;
    tokens = malloc(sizeof(char *) * (size + 1));
    tokens[size] = NULL;
    for (int i = 0; i < size; i++) {
        is_quoted = false;
        tokens[i] = get_token(input, &is_quoted);
        input = go_to_next(input, my_strlen(tokens[i]), is_quoted);
    }
    free(input_save);
    return tokens;
}
