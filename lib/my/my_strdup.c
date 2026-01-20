/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday08-21
** File description:
** my_strdup.c
*/

#include "stdlib.h"
#include "my.h"

char *my_strdup(char const *str)
{
    int len = my_strlen(str);
    char *buf = malloc(len + 1);

    if (!buf)
        return NULL;
    my_strcpy(buf, str);
    return buf;
}
