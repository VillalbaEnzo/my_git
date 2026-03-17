/*
** EPITECH PROJECT, 2026
** cuddle [WSL: Ubuntu]
** File description:
** find_column
*/

#include "dataframe.h"

int find_column(dataframe_t *df, const char *column)
{
    if (!df || !column)
        return -1;
    for (size_t i = 0; i < df->header->count; i++) {
        if (strcmp(df->header->columns[i].name, column) == 0)
            return i;
    }
    fprintf(stderr, "%s : Column not found.", column);
    return -1;
}
