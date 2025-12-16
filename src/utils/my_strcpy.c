/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-7
** File description:
** my_strcpy.c
*/

#include "../../include/my.h"

char *my_strcpy(char *dest, char const *src)
{
    for (int i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[my_strlen(src)] = '\0';
    return dest;
}
