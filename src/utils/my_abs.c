/*
** EPITECH PROJECT, 2025
** G-CPE-110-LYN-1-1-secured-14 [WSL: Ubuntu-24.04]
** File description:
** my_abs.c
*/

#include "my.h"

int my_abs(int nbr)
{
    if (nbr < 0)
        return nbr * -1;
    return nbr;
}
