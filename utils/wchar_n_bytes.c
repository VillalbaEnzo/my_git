/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** wchar_n_bytes.c
*/

#include "../include/my.h"

int wchar_n_bytes(wint_t wc)
{
    if (wc <= 0x7F)
        return 1;
    if (wc <= 0x7FF)
        return 2;
    if (wc <= 0xFFFF)
        return 3;
    if (wc <= 0x10FFFF)
        return 4;
    return 0;
}
