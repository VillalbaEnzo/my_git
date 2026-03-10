/*
** EPITECH PROJECT, 2026
** cuddle [WSL: Ubuntu]
** File description:
** inits
*/

#include "database.h"

header_t *init_header(void)
{
    header_t *temp = malloc(sizeof(header_t));

    if (temp == NULL)
        return NULL;
    temp->capacity = 4;
    temp->count = 0;
    temp->columns = malloc(sizeof(column_t) * temp->capacity);
    if (temp->columns == NULL)
        return NULL;
    else
        return temp;
}

rows_t *init_rows(void)
{
    rows_t *temp = malloc(sizeof(rows_t));

    if (temp == NULL)
        return NULL;
    temp->capacity = 4;
    temp->count = 0;
    temp->rows = malloc(sizeof(data_t *) * temp->capacity);
    if (temp->rows == NULL)
        return NULL;
    else
        return temp;
}
