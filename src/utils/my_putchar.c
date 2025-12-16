/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-7
** File description:
** my_putchar.c
*/

#include "my.h"

int my_putchar(char c)
{
    write(1, &c, 1);
    return 1;
}
