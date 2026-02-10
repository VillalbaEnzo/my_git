/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18 [WSL: Ubuntu-24.04]
** File description:
** get_sign
*/


#include "../include/my.h"

int get_sign_char_int(long long value, format_spec_t *spec)
{
    if (value < 0)
        return '-';
    if (spec->flags & FLAG_PLUS)
        return '+';
    if (spec->flags & FLAG_SPACE)
        return ' ';
    return 0;
}

int get_sign_char_float(double value, format_spec_t *spec)
{
    if (value < 0)
        return '-';
    if (spec->flags & FLAG_PLUS)
        return '+';
    if (spec->flags & FLAG_SPACE)
        return ' ';
    return 0;
}
