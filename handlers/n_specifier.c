/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** n_specifier.c
*/

#include "../include/my.h"

static void handle_n_short(format_spec_t *spec, void *ptr)
{
    if (spec->length == 'h')
        *(short *)ptr = (short)spec->chars_written;
    if (spec->length == 'H')
        *(signed char *)ptr = (signed char)spec->chars_written;
}

static void handle_n_long(format_spec_t *spec, void *ptr)
{
    if (spec->length == 'l')
        *(long *)ptr = (long)spec->chars_written;
    if (spec->length == 'L')
        *(long long *)ptr = (long long)spec->chars_written;
}

int handle_n(format_spec_t *spec, va_list args)
{
    int *ptr = va_arg(args, int *);

    if (ptr == NULL)
        return 0;
    if (spec->length == 'h' || spec->length == 'H') {
        handle_n_short(spec, ptr);
        return 0;
    }
    if (spec->length == 'l' || spec->length == 'L') {
        handle_n_long(spec, ptr);
        return 0;
    }
    *ptr = spec->chars_written;
    return 0;
}
