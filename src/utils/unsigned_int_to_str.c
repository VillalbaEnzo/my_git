/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-myls-7
** File description:
** my_getnbr.c
*/

#include "../include/my.h"

char *unsigned_int_to_str(unsigned int n)
{
    char *str;
    int i = 0;

    if (n == 0) {
        str = malloc(sizeof(char) * 2);
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
    str = malloc(sizeof(char) * 12);
    if (str == NULL)
        return NULL;
    while (n > 0) {
        str[i] = (n % 10) + '0';
        n = n / 10;
        i++;
    }
    str[i] = '\0';
    my_revstr(str);
    return str;
}
