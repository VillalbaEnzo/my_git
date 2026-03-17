/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** get_value
*/

#include "dataframe.h"

void **df_get_values(dataframe_t *dataframe, const char *column)
{
    int columns_idx = -1;
    void **values = NULL;

    if (!dataframe || !dataframe->header || !dataframe->data || !column)
        return NULL;
    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (strcmp(dataframe->header->columns[i].name, column) == 0) {
            columns_idx = i;
            break;
        }
    }
    if (columns_idx == -1)
        return NULL;
    values = malloc(sizeof(void *) * (dataframe->nb_rows + 1));
    if (!values)
        return NULL;
    for (int i = 0; i < dataframe->nb_rows; i++)
        values[i] = return_value(dataframe, i, columns_idx);
    values[dataframe->nb_rows] = NULL;
    return values;
}
