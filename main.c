/*
** EPITECH PROJECT, 2025
** Stumper
** File description:
** main.c
*/

#include "my.h"

int main(int argc, char **argv)
{
    float denom = 0;
    float numer = 0;

    if (argc < 2)
        return 84;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] < 'A' || argv[i][0] > 'E'
            || argv[i][1] != ',' || !is_num(argv[i] + 2))
            return 84;
        denom += (float)atoi(argv[i] + 2);
        numer += (float)calculate_one_grade(argv[i][0], atoi(argv[i] + 2));
    }
    if (denom == 0)
        return 84;
    printf("%.2f\n", numer / denom);
    return 0;
}
