/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** free_model.c
*/

#include "my.h"

void free_model(model_t *model)
{
    if (!model->layers)
        return;
    for (int i = 0; i < model->count; i++) {
        if (model->layers[i].data)
            free(model->layers[i].data);
    }
    free(model->layers);
}