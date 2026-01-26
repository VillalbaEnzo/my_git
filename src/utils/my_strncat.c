/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday07-8
** File description:
** my_strncat.c
*/

#include "../include/my.h"



char *my_strncat(char *dest, char const *src, int nb)
{
    my_strncpy(&dest[my_strlen(dest)], src, nb);
    return dest;
}
