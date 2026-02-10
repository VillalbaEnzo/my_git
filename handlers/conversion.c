/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** conversion.c
*/

#include "../include/my.h"

int handle_conversion_part2(format_spec_t *spec, va_list args)
{
    char c = spec->specifier;

    if (c == 'x' || c == 'X')
        return handle_hexa(spec, args);
    if (c == 'p')
        return handle_pointer(spec, args);
    if (c == 'n')
        return handle_n(spec, args);
    if (c == 'a' || c == 'A')
        return handle_hexa_float(spec, args);
    return 0;
}

int handle_conversion(format_spec_t *spec, va_list args)
{
    char c = spec->specifier;

    if (c == 'd' || c == 'i')
        return handle_int(spec, args);
    if (c == 'u')
        return handle_unsigned(spec, args);
    if (c == 'c')
        return handle_char(spec, args);
    if (c == 's')
        return handle_str(spec, args);
    if (c == 'f' || c == 'F')
        return handle_float(spec, args);
    if (c == 'e' || c == 'E')
        return handle_scientific(spec, args);
    if (c == 'g' || c == 'G')
        return handle_float_auto(spec, args);
    if (c == 'o')
        return handle_octal(spec, args);
    return handle_conversion_part2(spec, args);
}
