/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** wchar.c
*/

#include "../include/my.h"

void put_wchar_1byte(wint_t wc, int *count)
{
    *count += my_putchar(wc);
}

void put_wchar_2bytes(wint_t wc, int *count)
{
    *count += my_putchar((wc >> 6) | 0xC0);
    *count += my_putchar((wc & 0x3F) | 0x80);
}

void put_wchar_3bytes(wint_t wc, int *count)
{
    *count += my_putchar((wc >> 12) | 0xE0);
    *count += my_putchar(((wc >> 6) & 0x3F) | 0x80);
    *count += my_putchar((wc & 0x3F) | 0x80);
}

void put_wchar_4bytes(wint_t wc, int *count)
{
    *count += my_putchar((wc >> 18) | 0xF0);
    *count += my_putchar(((wc >> 12) & 0x3F) | 0x80);
    *count += my_putchar(((wc >> 6) & 0x3F) | 0x80);
    *count += my_putchar((wc & 0x3F) | 0x80);
}
