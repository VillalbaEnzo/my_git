/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-7
** File description:
** my_putstr.c
*/

#include "../include/my.h"

int my_putstr(char const *str)
{
    int i = 0;

    if (str == NULL)
        return my_putstr("(null)");
    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
    return i;
}
