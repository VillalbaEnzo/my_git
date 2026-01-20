/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-21
** File description:
** my_print_unsigned.c
*/

#include "../includes/my.h"

int my_print_unsigned(long nb)
{
    int d;

    if (nb < 0) {
        my_putchar('-');
        nb = nb - 1;
    }
    d = nb % 10;
    if (nb > 9)
        my_put_nbr((nb - d) / 10);
    my_putchar(d + '0');
    return 0;
}
