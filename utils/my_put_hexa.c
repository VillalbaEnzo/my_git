/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** my_put_hexa.c
*/

#include "../include/my.h"

static int print_hex_digits(char *hexa_number, int i)
{
    int count = 0;

    for (int j = i - 1; j >= 0; j--)
        count += my_putchar(hexa_number[j]);
    return count;
}

static int fill_hexa_buffer(unsigned long long nbr,
    char *buffer, char specifier)
{
    const char *digits_lower = "0123456789abcdef";
    const char *digits_upper = "0123456789ABCDEF";
    const char *digits = (specifier == 'X') ? digits_upper : digits_lower;
    int i = 0;

    while (nbr != 0) {
        buffer[i] = digits[nbr % 16];
        nbr = nbr / 16;
        i++;
    }
    return i;
}

int my_put_hexa(unsigned long long number, format_spec_t *spec)
{
    char hexa_number[20];
    int i = 0;
    int count = 0;

    if (number == 0)
        return my_putchar('0');
    i = fill_hexa_buffer(number, hexa_number, spec->specifier);
    count = print_hex_digits(hexa_number, i);
    return count;
}
