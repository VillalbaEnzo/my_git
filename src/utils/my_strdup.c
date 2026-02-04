/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday08-8
** File description:
** my_strdup.c
*/

#include "../include/my.h"

char *my_strdup(char const *src)
{
    char *str = malloc(sizeof(*str) * my_strlen(src) + 1);

    for (int i = 0; i < my_strlen(src); i++) {
        str[i] = src[i];
    }
    return str;
}
