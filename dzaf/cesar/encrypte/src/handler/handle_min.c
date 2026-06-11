/*
** EPITECH PROJECT, 2025
** next
** File description:
** main.c
*/

#include "my.h"

char handle_min(char c, int n)
{
    if ((c - n) < 'a')
        return (c - n + 26);
    if ((c - n) > 'z')
        return (c - n - 26);
    return (c - n);
}
