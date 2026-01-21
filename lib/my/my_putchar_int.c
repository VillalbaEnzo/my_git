/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-21
** File description:
** my_putchar_int.c
*/

#include "../includes/my.h"

int my_putchar_int(char c)
{
    write(1, &c, 1);
    return 0;
}

int my_putchar_int_maj(char c)
{
    if (c >= 'a' && c <= 'z')
        c = c - 'a' + 'A';
    write(1, &c, 1);
    return 0;
}
