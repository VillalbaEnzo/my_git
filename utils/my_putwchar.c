/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** my_putwchar.c
*/

#include "../include/my.h"

void my_putwchar(wint_t wc, int *count)
{
    if (wc <= 0x7F)
        return put_wchar_1byte(wc, count);
    if (wc <= 0x7FF)
        return put_wchar_2bytes(wc, count);
    if (wc <= 0xFFFF)
        return put_wchar_3bytes(wc, count);
    if (wc <= 0x10FFFF)
        put_wchar_4bytes(wc, count);
}
