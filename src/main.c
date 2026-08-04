/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** main.c
*/

#include "my.h"

static bool handle_error(model_t *model, int ac, char **av)
{
    if (!model->layers)
        return false;
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
    model_t model;
    model.count = 4;
    model.layers = calloc(model.count, sizeof(matrix_t));

    if (!handle_error(&model, argc, argv)) {
        free_model(&model);
        free(model.layers);
        return 84;
    }
    if (!parsing(&model, argc, argv)) {
        free_model(&model);
        free(model.layers);
        return 84;
    }
    free_model(&model);
    // free(model.layers);
    return 0;
}
