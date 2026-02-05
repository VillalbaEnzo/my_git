/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-bsminiprintf-15
** File description:
** mini_printf.c
*/

#include "../include/my.h"

int if_func(const char *format, int *i, va_list args)
{
    if (format[*i] == '%' && format[*i + 1] == 'd') {
        my_put_nbr(va_arg(args, int));
        return 1;
    }
    if (format[*i] == '%' && format[*i + 1] == 's') {
        my_putstr(va_arg(args, char*));
        return 1;
    }
    if (format[*i] == '%' && format[*i + 1] == 'i') {
        my_put_nbr(va_arg(args, int));
        return 1;
    }
    if (format[*i] == '%' && format[*i + 1] == 'u') {
        my_put_nbr_u(va_arg(args, unsigned int), 0);
        return 1;
    }
    return 0;
}

void flags(const char *format, va_list args)
{
    for (int i = 0; format[i] != '\0'; i++) {
        if (if_func(format, &i, args) == 1) {
            i++;
            continue;
        }
        if (format[i] == '%' && format[i + 1] == 'c') {
            my_putchar(va_arg(args, int));
            i++;
            continue;
        }
        if (format[i] == '%' && format[i + 1] == '%') {
            my_putchar('%');
            i++;
            continue;
        }
        my_putchar(format[i]);
    }
    return;
}

int mini_printf(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    flags(format, args);
    va_end(args);
    return 0;
}
