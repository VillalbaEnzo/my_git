/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** my_put_nbr_octal.c
*/

#include "../include/my.h"

int my_put_nbr_octal(unsigned long long nb)
{
    int count = 0;

    if (nb >= 8) {
        count += my_put_nbr_octal(nb / 8);
    }
    count += my_putchar((nb % 8) + '0');
    return count;
}
