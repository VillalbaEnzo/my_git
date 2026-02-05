/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday05-26
** File description:
** my_find_prime_sup.c
*/

#include "../include/my.h"



int my_find_prime_sup(int nb)
{
    int i = nb;

    if (nb < 0) {
        return 2;
    }
    if (my_is_prime(nb) == 1) {
        return nb;
    }
    while (my_is_prime(i) != 1) {
        i++;
    }
    return i;
}
