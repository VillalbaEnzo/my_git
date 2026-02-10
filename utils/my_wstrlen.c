/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** my_wstrlen.c
*/

#include "../include/my.h"

int my_wstrlen(const wchar_t *wstr)
{
    int len = 0;

    if (!wstr)
        return 0;
    while (wstr[len] != 0) {
        len++;
    }
    return len;
}
