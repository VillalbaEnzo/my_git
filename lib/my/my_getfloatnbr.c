/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** my_getfloatnbr.c
*/

#include "../includes/my.h"
#include <unistd.h>

static int count_minus(char const *str)
{
    int sign = 0;

    if (str == NULL)
        return 84;
    for (int i = 0; str[i] && (str[i] == '+' || str[i] == '-'); i++) {
        if (str[i] == '+')
            sign++;
        if (str[i] == '-')
            sign--;
    }
    return sign;
}

static float parse_integer_part(char const *str, int *i)
{
    float nb = 0.0;

    while (str[*i] && str[*i] >= '0' && str[*i] <= '9') {
        nb = nb * 10.0 + (str[*i] - '0');
        (*i)++;
    }
    return nb;
}

static float parse_decimal_part(char const *str, int *i)
{
    float decimal = 0.0;
    float divisor = 10.0;

    if (str[*i] == '.') {
        (*i)++;
        while (str[*i] && str[*i] >= '0' && str[*i] <= '9') {
            decimal += (str[*i] - '0') / divisor;
            divisor *= 10.0;
            (*i)++;
        }
    }
    return decimal;
}

static void skip_signs(char const *str, int *i)
{
    while (str[*i] && (str[*i] == '+' || str[*i] == '-'))
        (*i)++;
}

float my_getfloatnbr(char const *str)
{
    int sign = 0;
    float nb = 0.0;
    int i = 0;

    if (str == NULL)
        return 84.0;
    sign = count_minus(str);
    skip_signs(str, &i);
    nb = parse_integer_part(str, &i);
    nb += parse_decimal_part(str, &i);
    return (sign >= 0) ? nb : -nb;
}
