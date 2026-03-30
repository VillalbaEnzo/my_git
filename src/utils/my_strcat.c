/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-robotfactory-5 [WSL: Ubuntu-24.04]
** File description:
** my_strcat.c
*/

#include "op.h"

char *my_strcat(char *dest, char const *src)
{
    my_strcpy(&dest[my_strlen(dest)], src);
    return dest;
}
