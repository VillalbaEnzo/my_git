/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** train_tokenizer.c
*/

#include "my.h"

void tokenizer(const char *filepath, int vocab_target_size)
{
    text_buffer_t buffer = init_text_buffer(filepath, true);
    vocab_node_t *vocab = NULL;

    int current_id = 256;
    printf("Demarrage de l'entrainement BPE...\n");
    while (current_id < vocab_target_size) {
        char *pair = get_pair(buffer);
        if (!pair)
            break;
        vocab = create_node(vocab, current_id, pair);
        apply_fusion(&buffer, pair);
        printf("Token %d cree : %s\n", current_id, pair);
        current_id++;
    }
    save_vocab(vocab, "vocab.txt");
    free_list(vocab);
}
