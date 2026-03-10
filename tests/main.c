/*
** EPITECH PROJECT, 2026
** cuddle [WSL: Ubuntu]
** File description:
** main
*/

#include "database.h"

int main(void)
{
    dataframe_t *df = df_read_csv("tests/test_short.csv", ";");
    dataframe_shape_t shape = df_shape(df);

    printf("Shape: %d rows, %d columns\n", shape.nb_rows, shape.nb_columns);
    return 0;
}
