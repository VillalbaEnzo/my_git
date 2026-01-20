/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-miniprintf-38
** File description:
** my_put_nbr.c
*/

#include "../includes/my.h"
#include <unistd.h>

int my_put_nbr(long nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10)
        my_put_nbr(nb / 10);
    my_putchar((nb % 10) + '0');
    return 0;
}
