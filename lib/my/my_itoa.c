/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-17
** File description:
** my_itoa.c
*/

#include "my.h"

static void handle_zero(char *str)
{
    str[0] = '0';
    str[1] = '\0';
}

static void convert_to_string(int number, char *str, int *index)
{
    int digit;

    while (number > 0) {
        digit = number % 10;
        str[*index] = digit + '0';
        (*index)++;
        number /= 10;
    }
}

char *my_itoa(int nb, char *str)
{
    int i = 0;

    if (nb == 0) {
        handle_zero(str);
        return str;
    }
    convert_to_string(nb, str, &i);
    str[i] = '\0';
    my_revstr(str);
    return str;
}
