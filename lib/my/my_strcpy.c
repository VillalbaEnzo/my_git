/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-25
** File description:
** my_strcpy.c
*/

#include "../includes/my.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *my_strcpy(char *dest, const char *src)
{
    int i = 0;

    if (src == NULL || dest == NULL)
        return NULL;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
