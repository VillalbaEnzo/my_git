/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** my_putnwstr.c
*/

#include "../include/my.h"

void my_putnwstr(const wchar_t *wstr, int n, int *count)
{
    if (!wstr)
        return;
    for (int i = 0; i < n && wstr[i] != 0; i++)
        my_putwchar(wstr[i], count);
}
