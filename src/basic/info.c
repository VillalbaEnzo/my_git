/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-2 [WSL: Ubuntu-24.04]
** File description:
** info.c
*/

#include "dataframe.h"

static char *get_type_name(column_type_t type)
{
    if (type == BOOL)
        return "bool";
    if (type == INT)
        return "int";
    if (type == UINT)
        return "unsigned int";
    if (type == FLOAT)
        return "float";
    if (type == STRING)
        return "string";
    return "undefined";
}

void df_info(dataframe_t *dataframe)
{
    if (!dataframe || !dataframe->header)
        return;
    printf("%d columns:\n", dataframe->nb_columns);
    for (int i = 0; i < dataframe->nb_columns; i++)
        printf("%s: %s\n", dataframe->header->columns[i].name,
            get_type_name(dataframe->header->columns[i].type));
}
