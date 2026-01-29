/*
** EPITECH PROJECT, 2025
** Day3
** File description:
** my_isneg.c
*/

#include "../include/my.h"



int my_isneg(int ascii)
{
    if (ascii < 0) {
        my_putchar(78);
    } else {
        my_putchar(80);
    }
    my_putchar('\n');
    return 0;
}
