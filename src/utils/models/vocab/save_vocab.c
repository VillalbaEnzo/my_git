/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** save_vocab.c
*/

#include "my.h"

bool save_vocab(vocab_node_t *head, const char *filename)
{
    vocab_node_t *temp = head;
    FILE *stream;

    stream = fopen(filename, "w");
    if (!stream)
        return false;
    while (temp) {
        fprintf(stream, "%d:%s\n", temp->id, temp->token);
        temp = temp->next;
    }
    fclose(stream);
    return true;
}
