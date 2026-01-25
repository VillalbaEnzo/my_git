/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday05-26
** File description:
** my_compute_square_root.c
*/

#include "../include/my.h"



int my_compute_square_root(int nb)
{
    if (nb < 0)
        return 0;
    for (int i = 0; i * i <= nb; i++) {
        if (i * i == nb)
            return i;
    }
    return 0;
}
