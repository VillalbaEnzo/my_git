/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** load_voca.c
*/

#include "my.h"

vocab_node_t *load_vocab(const char *filepath)
{
    char **file = get_file((char *)filepath);
    vocab_node_t *head = NULL;

    if (!file)
        return NULL;
    for (int i = 0; file[i]; i++) {
        char *sep = strchr(file[i], ':');
        if (!sep)
            continue;
        *sep = '\0';
        head = create_node(head, atoi(file[i]), sep + 1);
    }
    free_array(file);
    return head;
}
