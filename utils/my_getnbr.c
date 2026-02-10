/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18 [WSL: Ubuntu-24.04]
** File description:
** my_getnbr
*/

#include "../include/my.h"

int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int check_maxint(int signe, int nb, int digit)
{
    if (signe == 1 && (nb > 214748364 || (nb == 214748364 && digit > 7)))
        return 0;
    if (signe == -1 && (nb > 214748364 || (nb == 214748364 && digit > 8)))
        return 0;
    return 1;
}

int my_getnbr(const char *str)
{
    int i = 0;
    int signe = 1;
    int nb = 0;
    int digit = 0;

    while (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-')
            signe *= -1;
        i++;
    }
    for (; str[i] != '\0'; i++) {
        if (!is_digit(str[i]))
            break;
        digit = str[i] - '0';
        nb = nb * 10 + digit;
        if (check_maxint(signe, nb, digit) == 0) {
            return 0;
        }
    }
    return nb * signe;
}
