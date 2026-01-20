/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** my_perror.c
*/

#include "my.h"
#include "unistd.h"

int my_perror(char const *str)
{
    int i = 0;

    if (str == NULL)
        return 84;
    while (str[i] != '\0')
        i++;
    write(2, str, i);
    return 0;
}
