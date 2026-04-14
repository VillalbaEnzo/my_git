/*
** EPITECH PROJECT, 2025
** my_putchar.c
** File description:
** my_putchar
*/
#include "mysh.h"

void my_putchar(char c, int fd)
{
    write(fd, &c, 1);
}
