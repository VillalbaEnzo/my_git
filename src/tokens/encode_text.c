/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** encode_text.c
*/

#include "my.h"

static int get_token_id(vocab_node_t *head, char *token)
{
    vocab_node_t *temp = head;

    while (temp) {
        if (strcmp(temp->token, token) == 0)
            return temp->id;
        temp = temp->next;
    }
    return (int)token[0];
}

int *encode_text(const char *user_input, vocab_node_t *head, int *out_size)
{
    if (!head || !user_input)
        return NULL;

    text_buffer_t buffer = init_text_buffer(user_input, false);
    vocab_node_t *temp = head;

    while (temp) {
        apply_fusion(&buffer, temp->token);
        temp = temp->next;
    }
    int *ids = calloc(buffer.size, sizeof(int));
    if (!ids)
        return NULL;
    for (int i = 0; i < buffer.size; i++)
        ids[i] = get_token_id(head, buffer.tokens[i]);
    *out_size = buffer.size;
    free_array(buffer.tokens);
    return ids;
}
