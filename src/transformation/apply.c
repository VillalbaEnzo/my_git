/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** apply
*/

#include "dataframe.h"

void apply_to_data(data_t *to_apply, column_type_t type,
    void *(*apply_func)(void *value))
{
    switch (type) {
        case INT:
            to_apply->i_value = *(int *)apply_func(&(to_apply->i_value));
            return;
        case UINT:
            to_apply->ui_value = *(unsigned int *)(&(to_apply->ui_value));
            return;
        case FLOAT:
            to_apply->f_value = *(float *)apply_func(&(to_apply->f_value));
            return;
        case STRING:
            to_apply->c_value = (char *)apply_func(&(to_apply->c_value));
            return;
        case BOOL:
            to_apply->b_value = *(bool *)apply_func(&(to_apply->b_value));
            return;
        case UNDEFINED:
            return;
    }
}

dataframe_t *df_apply(dataframe_t *dataframe, const char *column,
    void *(*apply_func)(void *value))
{
    int column_idx = 0;
    dataframe_t *apply_df = NULL;

    if (!dataframe || !column || !apply_func)
        return NULL;
    apply_df = copy_df(dataframe);
    if (!apply_df)
        return NULL;
    column_idx = find_column(apply_df, column);
    if (column_idx == -1)
        return NULL;
    for (size_t i = 0; i < apply_df->data->count; i++)
        apply_to_data(&(apply_df->data->rows[i][column_idx]),
            apply_df->header->columns[column_idx].type, apply_func);
    return apply_df;
}
