/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday07-24
** File description:
** my_putchar.c
*/

#include "../includes/my.h"
#include "unistd.h"

void my_putchar(char c)
{
    write(1, &c, 1);
    return;
}
