/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** my_putnstr.c
*/

#include "../include/my.h"

int my_putnstr(const char *str, int n)
{
    int i = 0;

    if (!str)
        return 0;
    for (i = 0; i < n && str[i] != '\0'; i++) {
        my_putchar(str[i]);
    }
    return i;
}
