/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday04-19
** File description:
** my_getnbr.c
*/

#include "../include/my.h"

static int space(char const *str, int i)
{
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i++;
    return i;
}

static int sign_func(char const *str, int *i)
{
    int sign = 1;

    while (str[*i] == '-' || str[*i] == '+') {
        if (str[*i] == '-')
            sign = -sign;
        (*i)++;
    }
    return sign;
}

static int extremite(char const *str, int *i, int sign)
{
    int res = 0;
    int digit;

    while (str[*i] >= '0' && str[*i] <= '9') {
        digit = str[*i] - '0';
        if (sign == 1 && res > (INT_MAX - digit) / 10)
            return 0;
        if (sign == -1 && -res < (INT_MIN + digit) / 10)
            return 0;
        res = res * 10 + digit;
        (*i)++;
    }
    return res * sign;
}

int my_getnbr(char const *str)
{
    int i = 0;
    int sign = 1;
    int res = 0;

    i = space(str, i);
    sign = sign_func(str, &i);
    res = extremite(str, &i, sign);
    return res;
}
