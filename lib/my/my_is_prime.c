/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday05-48
** File description:
** my_is_prime.c
*/

#include "../includes/my.h"

int my_is_prime(int nb)
{
    int i = 0;
    int i2 = 0;

    if (nb <= 0)
        return 0;
    for (; i2 <= nb; i++) {
        i2 = i * i;
        if (nb % i == 0)
            return 1;
    }
    return 0;
}
