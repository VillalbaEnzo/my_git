/*
** EPITECH PROJECT, 2026
** cuddle [WSL: Ubuntu]
** File description:
** main
*/

#include "database.h"

int main(void)
{
    dataframe_t *dataframe = df_read_csv("tests/test_short.csv", NULL);
    void **values = df_get_values(dataframe, "Identifier");

    while (*values) {
        printf("Value: %d\n", *(int *)*values);
        values++;
    }
}
