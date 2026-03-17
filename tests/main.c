/*
** EPITECH PROJECT, 2026
** cuddle [WSL: Ubuntu]
** File description:
** main
*/

#include "dataframe.h"

bool sort_func(void *value1, void *value2) {
    return *(int *)value1 > *(int *)value2;
}

int main(void)
{
    dataframe_t *dataframe = df_read_csv("tests/mouli_test.csv", ";");
    dataframe_t *sorted = df_sort(dataframe, "age", sort_func);

    df_write_csv(sorted, "write_in_this.csv");
    df_free(dataframe);
    df_free(sorted);
    return 0;
}
