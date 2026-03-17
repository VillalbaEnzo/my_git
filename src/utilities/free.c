/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-2 [WSL: Ubuntu-24.04]
** File description:
** free.c
*/

#include "dataframe.h"

static void free_row_strings(data_t *row, int nb_columns)
{
    for (int j = 0; j < nb_columns; j++) {
        if (row[j].data_type == STRING && row[j].c_value)
            free(row[j].c_value);
    }
}

static void free_data(dataframe_t *dataframe)
{
    if (!dataframe->data)
        return;
    if (!dataframe->data->rows) {
        free(dataframe->data);
        return;
    }
    for (size_t i = 0; i < dataframe->data->count; i++) {
        if (!dataframe->data->rows[i])
            continue;
        free_row_strings(dataframe->data->rows[i], dataframe->nb_columns);
        free(dataframe->data->rows[i]);
    }
    free(dataframe->data->rows);
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
    for (size_t i = 0; i < dataframe->header->count; i++) {
        if (dataframe->header->columns[i].name)
            free((char *)dataframe->header->columns[i].name);
    }
    free(dataframe->header->columns);
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
