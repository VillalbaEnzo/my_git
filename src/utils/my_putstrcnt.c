/*
** EPITECH PROJECT, 2025
** my_putstr
** File description:
** Displays one-by-one the characters of a string
*/
#include "mysh.h"
#include "utils.h"

int my_putstr(char const *str, int fd)
{
    int i = 0;

    for (i = 0; str[i] != '\0'; i++) {
        my_putchar(str[i], fd);
    }
    return i;
}
