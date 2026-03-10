/*
** EPITECH PROJECT, 2026
** cuddle [WSL: Ubuntu]
** File description:
** resizes
*/

#include "database.h"

header_t *resize_header(header_t *header)
{
    header->capacity *= 2;
    header->columns = (column_t *)realloc(header->columns, header->capacity
        * sizeof(column_t));
    if (header->columns == NULL)
        return NULL;
    return header;
}

rows_t *resize_rows(rows_t *data)
{
    data->capacity *= 2;
    data->rows = (data_t **)realloc(data->rows, data->capacity
        * sizeof(data_t *));
    if (data->rows == NULL)
        return NULL;
    return data;
}
