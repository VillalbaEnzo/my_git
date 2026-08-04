/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** load_model.c
*/

#include "my.h"

bool load_model(model_t *model, const char *filename)
{
    FILE *stream = fopen(filename, "rb");
    size_t len = 0;

    if (!stream)
        return false;
    if (fread(&model->count, sizeof(int), 1, stream) != 1) {
        fclose(stream);
        return false;
    }
    model->layers = calloc(model->count, sizeof(matrix_t));
    for (int i = 0; i < model->count; i++) {
        if (fread(&model->layers[i].line, sizeof(int), 1, stream) != 1) {
            fclose(stream);
            free_model(model);
            return false;
        }
        if (fread(&model->layers[i].column, sizeof(int), 1, stream) != 1) {
            fclose(stream);
            free_model(model);
            return false;
        }
        model->layers[i] = create_matrix(model->layers[i].line, model->layers[i].column);
        len = (size_t)model->layers[i].line * model->layers[i].column;
        if (fread(model->layers[i].data, sizeof(float), len, stream) != len) {
            free_model(model);
            fclose(stream);
            return false;
        }
    }
    fclose(stream);
    return true;
}
