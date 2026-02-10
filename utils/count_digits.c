/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18 [WSL: Ubuntu-24.04]
** File description:
** count_digits
*/

#include "../include/my.h"

int count_digits_signed(long long nb)
{
    int count = 0;

    if (nb == 0)
        return 1;
    if (nb < 0)
        nb = -nb;
    while (nb > 0) {
        count++;
        nb /= 10;
    }
    return count;
}

int count_digits_unsigned(unsigned long long nb)
{
    int count = 0;

    if (nb == 0)
        return 1;
    while (nb > 0) {
        count++;
        nb /= 10;
    }
    return count;
}
