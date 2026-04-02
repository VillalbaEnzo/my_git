/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday07-8
** File description:
** is_num.h
*/

#include "my.h"

int is_num(char *nbr)
{
    for (int i = 0; nbr[i]; i++) {
        if (nbr[i] < '0' || nbr[i] > '9')
            return 0;
    }
    return 1;
}
