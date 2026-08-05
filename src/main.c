/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** main.c
*/

#include "my.h"

static bool handle_error(model_t *model, int ac, char **av)
{
    if (ac != 3 && ac != 2)
        return false;
    return true;
}

static bool parsing(model_t *model, int ac, char **av)
{
    if (strcmp(av[1], "train") == 0 && ac == 3) {
        train(model, abs(atoi(av[2])));
        return true;
    }
    if (strcmp(av[1], "load") == 0 && ac == 3) {
        if (load_model(model, av[2])) {
            for (int i = 0; i < model->count; i++)
                print_matrix(model->layers[i]);
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    // model_t model = {4, NULL};

    // if (!handle_error(&model, argc, argv)) {
    //     free_model(&model);
    //     free(model.layers);
    //     return 84;
    // }
    // if (!parsing(&model, argc, argv)) {
    //     free_model(&model);
    //     free(model.layers);
    //     return 84;
    // }
    // free_model(&model);

        // vocab_node_t *vocab = NULL;

        // printf("1. Remplissage de la liste...\n");
        // vocab = create_node(vocab, 256, "ca");
        // vocab = create_node(vocab, 257, "tion");
        // vocab = create_node(vocab, 258, "ment");

        // printf("2. Sauvegarde dans vocab_test.txt...\n");
        // if (save_vocab(vocab, "vocab_test.txt"))
        //     printf("-> Succes !\n");
        // else
        //     printf("-> Echec !\n");

        // printf("3. Nettoyage de la memoire...\n");
        // free_list(vocab);

    // tokenizer("bible.txt", 1000);
    vocab_node_t *head = load_vocab("vocab.txt");
    print_chained_list(head);
    char *str_test = strdup("hello je suis enzo");

    text_buffer_t test = init_text_buffer(str_test, false);
    for (int i = 0; i < test.size; i++)
        printf("%s\n", test.tokens[i]);
    free_list(head);
    return 0;
}
