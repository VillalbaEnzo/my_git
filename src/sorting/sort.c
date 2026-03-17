/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-2 [WSL: Ubuntu-24.04]
** File description:
** sort.c
*/

#include "dataframe.h"

static void swap_rows(data_t **row1, data_t **row2)
{
    data_t *tmp = *row1;

    *row1 = *row2;
    *row2 = tmp;
}

static void apply_swap(dataframe_t *df, bool (*sort_func)(void *, void *),
    int col_idx, int j)
{
    void *val1;
    void *val2;

    val1 = return_value(df, j, col_idx);
    val2 = return_value(df, j + 1, col_idx);
    if (sort_func(val1, val2))
        swap_rows(&df->data->rows[j], &df->data->rows[j + 1]);
}

static void bubble_sort(dataframe_t *df, int col_idx,
    bool (*sort_func)(void *, void *))
{
    for (int i = 0; i < df->nb_rows - 1; i++) {
        for (int j = 0; j < df->nb_rows - i - 1; j++)
            apply_swap(df, sort_func, col_idx, j);
    }
}

dataframe_t *df_sort(dataframe_t *dataframe, const char *column,
    bool (*sort_func)(void *value1, void *value2))
{
    dataframe_t *df_cpy = NULL;
    int idx_col = -1;

    if (!dataframe || !dataframe->data || !dataframe->header
        || !column || !sort_func)
        return NULL;
    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (strcmp(dataframe->header->columns[i].name, column) == 0) {
            idx_col = i;
            break;
        }
    }
    if (idx_col == -1)
        return NULL;
    df_cpy = df_head(dataframe, dataframe->nb_rows);
    if (!df_cpy)
        return NULL;
    bubble_sort(df_cpy, idx_col, sort_func);
    return df_cpy;
}
