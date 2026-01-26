/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday08-8
** File description:
** my_strdup.c
*/

#include "../include/my.h"



char *my_strdup(char const *src)
{
    int str_size = my_strlen(src);
    char *str = malloc(sizeof(*str) * str_size + 1);

    if (!str)
        return NULL;
    for (int i = 0; i < str_size; i++) {
        str[i] = src[i];
    }
    str[str_size] = '\0';
    return str;
}
