/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** save_model.c
*/

#include "my.h"

bool save_model(model_t model, const char *filename)
{
    FILE *stream = fopen(filename, "wb");
    size_t n = 0;

    if (!stream)
        return false;
    if (fwrite(&model.count, sizeof(int), 1, stream) != 1) {
        fclose(stream);
        return false;
    }
    for (int i = 0; i < model.count; i++) {
        if (fwrite(&model.layers[i].line, sizeof(int), 1, stream) != 1) {
            fclose(stream);
            return false;
        }
        if (fwrite(&model.layers[i].column, sizeof(int), 1, stream) != 1) {
            fclose(stream);
            return false;
        }
        n = (size_t)model.layers[i].line * model.layers[i].column;
        if (fwrite(model.layers[i].data, sizeof(float), n, stream) != n) {
            fclose(stream);
            return false;
        }
    }
    fclose(stream);
    return true;
}
