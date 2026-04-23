/*
** EPITECH PROJECT, 2025
** next
** File description:
** handle_maj.c
*/

#include "my.h"

char handle_maj(char c, int n)
{
    if ((c + n) > 'Z')
        return (c + n - 26);
    if ((c + n) < 'A')
        return (c + n + 26);
    return (c + n);
}
