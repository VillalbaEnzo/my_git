/*
** EPITECH PROJECT, 2025
** next
** File description:
** main.c
*/

#include "my.h"

int is_alpha(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    return 0;
}
