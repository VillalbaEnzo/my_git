/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-7
** File description:
** my_strlowcase.c
*/

#include "../include/my.h"



char *my_strlowcase(char *str)
{
    for (int i = 0; i < my_strlen(str); i++) {
        if (str[i] < 'A' || str[i] > 'Z') {
            continue;
        } else {
            str[i] += 32;
        }
    }
    return str;
}
