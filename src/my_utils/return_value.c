/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-2 [WSL: Ubuntu-24.04]
** File description:
** return_value.c
*/

#include "database.h"

void *return_value(dataframe_t *dataframe, int row, int columns_idx)
{
    if (dataframe->header->columns[columns_idx].type == BOOL)
        return &(dataframe->data->rows[row][columns_idx].b_value);
    if (dataframe->header->columns[columns_idx].type == INT)
        return &(dataframe->data->rows[row][columns_idx].i_value);
    if (dataframe->header->columns[columns_idx].type == UINT)
        return &(dataframe->data->rows[row][columns_idx].ui_value);
    if (dataframe->header->columns[columns_idx].type == FLOAT)
        return &(dataframe->data->rows[row][columns_idx].f_value);
    if (dataframe->header->columns[columns_idx].type == STRING)
        return &(dataframe->data->rows[row][columns_idx].c_value);
    return NULL;
}
