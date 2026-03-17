/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** get_value
*/

#include "dataframe.h"

void *df_get_value(dataframe_t *dataframe, int row, const char *column)
{
    int columns_idx = -1;

    if (!dataframe || !dataframe->header || !dataframe->data
        || row < 0 || row >= dataframe->nb_rows || !column)
        return NULL;
    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (strcmp(dataframe->header->columns[i].name, column) == 0) {
            columns_idx = i;
            break;
        }
    }
    if (columns_idx == -1)
        return NULL;
    return return_value(dataframe, row, columns_idx);
}
