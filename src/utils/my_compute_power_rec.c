/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday05-26
** File description:
** my_compute_power_rec.c
*/

#include "../include/my.h"



int my_compute_power_rec(int nb, int p)
{
    if (p == 0) {
        return 1;
    }
    if (p < 0) {
        return 0;
    }
    return nb * my_compute_power_rec(nb, p - 1);
}
