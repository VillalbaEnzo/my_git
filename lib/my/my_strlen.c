/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday04-48
** File description:
** my_strlen.c
*/

#include "../includes/my.h"
#include "unistd.h"

int my_strlen(char const *str)
{
    int i = 0;

    for (; str[i]; i++);
    return i;
}
