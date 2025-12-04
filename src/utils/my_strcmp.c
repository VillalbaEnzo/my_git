/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-myls-7
** File description:
** my_strcmp.c
*/

#include "../include/my.h"

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
        i++;
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}
