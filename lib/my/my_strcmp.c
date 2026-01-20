/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-25
** File description:
** my_strcmp.c
*/

#include "../includes/my.h"
#include "unistd.h"

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    for (i = 0; s1[i] != '\0'
        && s2[i] != '\0' &&
        s1[i] == s2[i]; i++);
    return (s1[i] - s2[i]);
}
