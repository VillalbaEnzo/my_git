/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-2 [WSL: Ubuntu-24.04]
** File description:
** copy.c
*/

#include "dataframe.h"

header_t *copy_header(header_t *src_header)
{
    header_t *header_cpy = malloc(sizeof(header_t));

    if (!header_cpy)
        return NULL;
    header_cpy->capacity = src_header->capacity;
    header_cpy->count = src_header->count;
    header_cpy->columns = malloc(sizeof(column_t) * (src_header->capacity));
    if (!header_cpy->columns) {
        free(header_cpy);
        return NULL;
    }
    for (size_t i = 0; i < src_header->count; i++) {
        header_cpy->columns[i].name = strdup(src_header->columns[i].name);
        header_cpy->columns[i].type = src_header->columns[i].type;
    }
    return header_cpy;
}

data_t *copy_row(data_t *src_row, int nb_columns)
{
    data_t *data_cpy = NULL;

    data_cpy = malloc(sizeof(data_t) * (nb_columns));
    if (!data_cpy)
        return NULL;
    for (int i = 0; i < nb_columns; i++) {
        data_cpy[i].data_type = src_row[i].data_type;
        if (src_row[i].data_type == BOOL)
            data_cpy[i].b_value = src_row[i].b_value;
        if (src_row[i].data_type == FLOAT)
            data_cpy[i].f_value = src_row[i].f_value;
        if (src_row[i].data_type == INT)
            data_cpy[i].i_value = src_row[i].i_value;
        if (src_row[i].data_type == UINT)
            data_cpy[i].ui_value = src_row[i].ui_value;
        if (src_row[i].data_type == STRING)
            data_cpy[i].c_value = strdup(src_row[i].c_value);
    }
    return data_cpy;
}

dataframe_t *copy_df(dataframe_t *src)
{
    dataframe_t *new_df = malloc(sizeof(dataframe_t));

    if (!new_df)
        return NULL;
    new_df->separator = src->separator;
    new_df->nb_rows = src->nb_rows;
    new_df->nb_columns = src->nb_columns;
    new_df->header = copy_header(src->header);
    new_df->data = malloc(sizeof(data_t));
    if (!new_df->data)
        return NULL;
    new_df->data->capacity = new_df->nb_rows;
    new_df->data->count = new_df->nb_rows;
    new_df->data->rows = malloc(sizeof(data_t *) * new_df->nb_rows);
    if (!new_df->data->rows)
        return NULL;
    for (int i = 0; i < new_df->nb_rows; i++)
        new_df->data->rows[i] = copy_row(src->data->rows[i],
            src->nb_columns);
    return new_df;
}
