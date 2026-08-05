/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** get_pair.c
*/

#include "my.h"

char *get_pair(text_buffer_t buffer)
{
    int max_count = 0;
    char *pair = NULL;

    for (int i = 0; i < buffer.size - 1; i++) {
        int current_count = 0;
        for (int j = 0; j < buffer.size - 1; j++) {
            if (strcmp(buffer.tokens[i], buffer.tokens[j]) == 0 &&
                strcmp(buffer.tokens[i+1], buffer.tokens[j+1]) == 0)
                current_count++;
        }
        if (current_count > max_count) {
            max_count = current_count;
            char *current_pair = calloc(strlen(buffer.tokens[i]) + strlen(buffer.tokens[i+1]) + 1, sizeof(char));
            strcpy(current_pair, buffer.tokens[i]);
            strcat(current_pair, buffer.tokens[i+1]);
            free(pair);
            pair = current_pair;
        }
    }
    return pair;
}
