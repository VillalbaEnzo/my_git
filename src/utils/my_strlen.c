/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-myls-7
** File description:
** my_strlen.c
*/

#include "../../include/my.h"

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }
    return i;
}
