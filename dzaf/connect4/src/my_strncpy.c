/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-7
** File description:
** my_strncpy.c
*/

#include "my.h"

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    while (i < n) {
        if (src[i] != '\0') {
            dest[i] = src[i];
        } else {
            dest[i] = '\0';
        }
        i++;
    }
    return dest;
}
