/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18 [WSL: Ubuntu-24.04]
** File description:
** print_number
*/

#include "../include/my.h"

void print_number_signed(long long nb, int *count)
{
    if (nb / 10 != 0)
        print_number_signed(nb / 10, count);
    *count += my_putchar((nb % 10) + '0');
}

void print_number_unsigned(unsigned long long value, int *count)
{
    if (value / 10 != 0)
        print_number_unsigned(value / 10, count);
    *count += my_putchar((value % 10) + '0');
}
