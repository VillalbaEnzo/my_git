/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday05-26
** File description:
** my_is_prime.c
*/

#include "../include/my.h"



int my_is_prime(int nb)
{
    int a = 2;
    int res = 1;

    if (nb <= 0 || nb == 1) {
        return 0;
    }
    while (a < nb) {
        if (nb % a == 0) {
            res = 0;
            a++;
            continue;
        }
        a++;
    }
    return res;
}
