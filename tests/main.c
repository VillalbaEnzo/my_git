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

    df_write_csv(df, "write_in_this.csv");
    return 0;
}
