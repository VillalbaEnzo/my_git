/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-25
** File description:
** my_strncpy.c
*/

#include "../includes/my.h"
#include "unistd.h"

char *my_strncpy(char *dest, char *src, int n)
{
    int i = 0;

    if (dest == NULL || src == NULL || n < 0)
        return NULL;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    return dest;
}
