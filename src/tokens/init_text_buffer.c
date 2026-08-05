/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** init_text_buffer.c
*/

#include "my.h"

text_buffer_t init_text_buffer(const char *input, bool file)
{
    text_buffer_t buffer = {0};
    char *raw_text = NULL;

    if (file) {
        int fd = open(input, O_RDONLY);
        if (fd == -1)
            return buffer;
        raw_text = read_file(fd);
    } else raw_text = (char *)input;
    buffer.size = file ? strlen(raw_text) - 1 : strlen(raw_text);
    buffer.tokens = malloc(buffer.size * sizeof(char *));
    if (!buffer.tokens) {
        buffer.size = 0;
        return buffer;
    }
    for (int i = 0; i < buffer.size; i++) {
        buffer.tokens[i] = malloc(2 * sizeof(char));
        if (buffer.tokens[i]) {
            buffer.tokens[i][0] = raw_text[i];
            buffer.tokens[i][1] = '\0';
        }
    }
    return buffer;
}
