/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-2 [WSL: Ubuntu-24.04]
** File description:
** free.c
*/

#include "database.h"

static void free_data(dataframe_t *dataframe)
{
    if (!dataframe->data)
        return;
    if (!dataframe->data->rows[0]) {
        free(dataframe->data);
        return;
    }
    for (int i = 0; i < dataframe->data->count; i++) {
        if (dataframe->data->rows[i]->c_value)
            free(dataframe->data->rows[i]->c_value);
        free(dataframe->data->rows[i]);
    }
    free(dataframe->data);
}

static void free_header(dataframe_t *dataframe)
{
    if (!dataframe->header)
        return;
    if (!dataframe->header->columns) {
        free(dataframe->header);
        return;
    }
    if (dataframe->header->columns->name)
        free(dataframe->header->columns->name);
    free(dataframe->header);
}

void df_free(dataframe_t *dataframe)
{
    if (!dataframe)
        return;
    free_data(dataframe);
    free_header(dataframe);
    free(dataframe);
}
