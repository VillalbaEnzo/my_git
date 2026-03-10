/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** apply
*/

#include "database.h"

dataframe_t *df_apply(dataframe_t *dataframe, const char *column,
    void *(*apply_func)(void *value))
{
    (void)dataframe;
    (void)column;
    (void)apply_func;
    return NULL;
}
