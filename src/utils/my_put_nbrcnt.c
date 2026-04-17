/*
** EPITECH PROJECT, 2025
** my_put_nbr.c
** File description:
** my_put_nbr
*/
#include "utils.h"
#include <stdio.h>


int my_put_nbr(long nbr, int *cnt, int fd)
{
    *cnt += 1;
    if (nbr < 0) {
        my_putchar('-', fd);
        nbr *= -1;
        *cnt += 1;
    }
    if (nbr > 9) {
        my_put_nbr(nbr / 10, cnt, fd);
    }
    my_putchar((nbr % 10) + 48, fd);
    return *cnt;
}
