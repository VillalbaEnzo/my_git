/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-7
** File description:
** my_strcapitalize.c
*/

#include "../include/my.h"



char *my_strcapitalize(char *str)
{
    str = my_strlowcase(str);
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] >= 'a' && str[i] <= 'z')
            && (i == 0 || str[i - 1] == ' '
                || str[i - 1] == '+' || str[i - 1] == '-')) {
            str[i] = str[i] - 32;
        }
    }
    return (str);
}
