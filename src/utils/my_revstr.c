/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-7
** File description:
** my_revstr.c
*/

#include "../../include/my.h"

static void my_swap_char(char *a, char *b)
{
    char temp = *a;

    *a = *b;
    *b = temp;
}

char *my_revstr(char *str)
{
    int len = my_strlen(str);

    for (int i = 0; i < len / 2; i++)
        my_swap_char(&str[i], &str[len - 1 - i]);
    return str;
}
