/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday03-46
** File description:
** my_isneg.c
*/

#include "../includes/my.h"
#include "unistd.h"

int my_isneg(int n)
{
    if (n < 0)
        write(1, "N", 1);
    if (n >= 0)
        write(1, "P", 1);
    else
        return 84;
    return 0;
}
