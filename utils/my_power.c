/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** my_power.c
*/

#include "../include/my.h"

double my_power(double base, int exp)
{
    double result = 1.0;
    int abs_exp = (exp < 0) ? -exp : exp;

    for (int i = 0; i < abs_exp; i++)
        result *= base;
    if (exp < 0)
        result = 1.0 / result;
    return result;
}

double my_abs_double(double value)
{
    return (value < 0) ? -value : value;
}
