/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday05-26
** File description:
** my_putnbr.c
*/

#include "my.h"

int my_putnbr(int nb)
{
    int count = 0;

    if (nb == 0) {
        return my_putchar('0');
    }
    if (nb == -2147483648) {
        count += my_putchar('-');
        count += my_putchar('2');
        count += my_putnbr(147483648);
        return count;
    }
    if (nb < 0) {
        count += my_putchar('-');
        nb = -nb;
    }
    if (nb / 10 != 0)
        count += my_putnbr(nb / 10);
    count += my_putchar((nb % 10) + '0');
    return count;
}
