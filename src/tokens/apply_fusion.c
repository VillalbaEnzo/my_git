/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** apply_fusion.c
*/

#include "my.h"

void apply_fusion(text_buffer_t *buffer, char *pair)
{
    char *current_pair = NULL;

    for (int i = 0; i < buffer->size - 1; i++) {
        current_pair = calloc(strlen(buffer->tokens[i]) +
            strlen(buffer->tokens[i + 1]) + 1, sizeof(char));
        strcpy(current_pair, buffer->tokens[i]);
        strcat(current_pair, buffer->tokens[i + 1]);
        if (strcmp(current_pair, pair) == 0) {
            free(buffer->tokens[i]);
            free(buffer->tokens[i + 1]);
            buffer->tokens[i] = calloc(strlen(pair) + 1, sizeof(char));
            strcpy(buffer->tokens[i], pair);
            memmove(&buffer->tokens[i + 1], &buffer->tokens[i + 2],
                (buffer->size - i - 2) * sizeof(char *));
            buffer->size--;
        }
        free(current_pair);
    }
}
