/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday04-48
** File description:
** my_getnbr.c
*/

#include "../includes/my.h"
#include "unistd.h"

int count_minus(char const *str)
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

int my_getnbr(char const *str)
{
    int sign = 0;
    int nb = 0;
    int i = 0;

    if (str == NULL)
        return 84;
    sign = count_minus(str);
    while (str[i] && (str[i] == '+' || str[i] == '-'))
        i++;
    while (str[i] && str[i] >= '0' && str[i] <= '9') {
        nb = nb * 10 + (str[i] - '0');
        i++;
    }
    return (sign >= 0) ? nb : -nb;
}
