/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** head
*/

#include "dataframe.h"

static int df_general_cpy(dataframe_t *df_cpy, dataframe_t *df, int nb_rows)
{
    df_cpy->nb_columns = df->nb_columns;
    if (nb_rows > df->nb_rows)
        df_cpy->nb_rows = df->nb_rows;
    else df_cpy->nb_rows = nb_rows;
    df_cpy->separator = df->separator;
    df_cpy->header = copy_header(df->header);
    if (!df_cpy->header) {
        df_free(df_cpy);
        return 0;
    }
    df_cpy->data = malloc(sizeof(rows_t));
    if (!df_cpy->data) {
        df_free(df_cpy);
        return 0;
    }
    df_cpy->data->rows = NULL;
    return 1;
}

static int df_data_cpy(dataframe_t *df_cpy)
{
    df_cpy->data->capacity = df_cpy->nb_rows;
    if (df_cpy->data->capacity == 0)
        df_cpy->data->capacity = 1;
    df_cpy->data->rows = malloc(sizeof(data_t *) * df_cpy->data->capacity);
    if (!df_cpy->data->rows) {
        df_free(df_cpy);
        return 0;
    }
    for (size_t i = 0; i < df_cpy->data->capacity; i++)
        df_cpy->data->rows[i] = NULL;
    df_cpy->data->count = df_cpy->nb_rows;
    return 1;
}

static int df_rows_cpy(dataframe_t *df_cpy, dataframe_t *df)
{
    for (int i = 0; i < df_cpy->nb_rows; i++) {
        df_cpy->data->rows[i] = copy_row(df->data->rows[i],
            df->nb_columns);
        if (!df_cpy->data->rows[i]) {
            df_free(df_cpy);
            return 0;
        }
    }
    return 1;
}

dataframe_t *df_head(dataframe_t *dataframe, int nb_rows)
{
    dataframe_t *df_cpy = NULL;

    if (!dataframe || nb_rows < 0)
        return NULL;
    df_cpy = malloc(sizeof(dataframe_t));
    if (!df_cpy)
        return NULL;
    df_cpy->header = NULL;
    df_cpy->data = NULL;
    if (!df_general_cpy(df_cpy, dataframe, nb_rows))
        return NULL;
    if (!df_data_cpy(df_cpy))
        return NULL;
    if (!df_rows_cpy(df_cpy, dataframe))
        return NULL;
    return df_cpy;
}
