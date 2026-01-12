/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-miniprintf-38
** File description:
** main.c
*/

#include <stdarg.h>
#include <unistd.h>
#include "../includes/my.h"

static void print_arg2(char specifier, va_list *arg)
{
    if (specifier == '%')
        my_putchar('%');
    if (specifier == 'c')
        my_putchar((char)va_arg(*arg, int));
}

static void print_arg(char specifier, va_list *arg)
{
    if (specifier == 's') {
        my_putstr(va_arg(*arg, char const *));
    } else if (specifier == 'd' || specifier == 'i') {
        my_put_nbr(va_arg(*arg, int));
    } else {
        print_arg2(specifier, arg);
    }
}

static void handle_format_char(const char *format, int *i, va_list *arg)
{
    if (format[*i] == '%') {
        (*i)++;
        if (format[*i] == '\0')
            return;
        print_arg(format[*i], arg);
    } else {
        my_putchar(format[*i]);
    }
}

int mini_printf(const char *format, ...)
{
    va_list arg;

    if (format == NULL)
        return 84;
    va_start(arg, format);
    for (int i = 0; format[i] != '\0'; i++) {
        handle_format_char(format, &i, &arg);
    }
    va_end(arg);
    return 0;
}
