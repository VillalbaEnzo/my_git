/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-bsminimini_printf-15
** File description:
** mini_mini_printf.c
*/

#include "../include/my.h"

int if_func(const char *format, int *i, va_list args, int *count)
{
    if (format[*i] == '%' && format[*i + 1] == 'd') {
        *count += my_put_nbr(va_arg(args, int));
        return 1;
    }
    if (format[*i] == '%' && format[*i + 1] == 's') {
        *count += my_putstr(va_arg(args, char*));
        return 1;
    }
    if (format[*i] == '%' && format[*i + 1] == 'i') {
        *count += my_put_nbr(va_arg(args, int));
        return 1;
    }
    return 0;
}

int flags(const char *format, va_list args)
{
    int count = 0;

    for (int i = 0; format[i] != '\0'; i++) {
        if (if_func(format, &i, args, &count) == 1) {
            i++;
            continue;
        }
        if (format[i] == '%' && format[i + 1] == 'c') {
            count += my_putchar(va_arg(args, int));
            i++;
            continue;
        }
        if (format[i] == '%' && format[i + 1] == '%') {
            count += my_putchar('%');
            i++;
            continue;
        }
        count += my_putchar(format[i]);
    }
    return count;
}

int mini_printf(const char *format, ...)
{
    va_list args;
    int count;

    va_start(args, format);
    count = flags(format, args);
    va_end(args);
    return count;
}
