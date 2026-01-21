/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-25
** File description:
** my_revstr.c
*/

#include "../includes/my.h"
#include "unistd.h"

int my_strlen_rev_str(char *str)
{
    int len = 0;

    while (str[len] != '\0')
        len++;
    return len;
}

char *my_revstr(char *str)
{
    int len = 0;
    int i = 0;
    int j = 0;
    char temp;

    if (str == NULL)
        return NULL;
    len = my_strlen_rev_str(str);
    j = len - 1;
    for (i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        j--;
    }
    return str;
}
