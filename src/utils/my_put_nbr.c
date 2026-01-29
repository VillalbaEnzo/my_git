/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday05-26
** File description:
** my_put_nbr.c
*/

#include "../include/my.h"



int my_put_nbr(int nb)
{
    if (nb == 0) {
        my_putchar('0');
        return 0;
    }
    if (nb == -2147483648) {
        my_putchar('-');
        my_putchar('2');
        my_put_nbr(147483648);
        return 0;
    }
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb >= 1) {
        if (nb / 10 != 0)
            my_put_nbr(nb / 10);
        my_putchar((nb % 10) + '0');
    }
    return 0;
}
