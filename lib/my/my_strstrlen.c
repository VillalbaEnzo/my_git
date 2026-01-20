/*
** EPITECH PROJECT, 2025
** ls_temp
** File description:
** my_strstrlen.c
*/

#include "my.h"

int my_strstrlen(char **str)
{
    int i = 0;

    if (str == NULL)
        return 0;
    while (str[i])
        i++;
    return i;
}
