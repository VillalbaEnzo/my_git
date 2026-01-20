/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-21
** File description:
** my_printf.c
*/

#include <stdarg.h>
#include <unistd.h>
#include "../includes/my.h"

static int dispatch_2(char specifier, va_list *arg)
{
    switch (specifier) {
        case 'c':
            return my_putchar_int((char)va_arg(*arg, int));
        case 'C':
            return my_putchar_int_maj((char)va_arg(*arg, int));
        case 'u':
            return my_print_unsigned(va_arg(*arg, unsigned int));
        case 'o':
            return my_octal(va_arg(*arg, unsigned int));
        case 'x':
            return my_hexadecimal(va_arg(*arg, unsigned int));
        case 'p':
            return my_adresse(va_arg(*arg, unsigned int));
        default:
            return 0;
    }
}

static int dispatch(char specifier, va_list *arg)
{
    switch (specifier) {
        case 's':
            return my_putstr(va_arg(*arg, char const *));
        case 'S':
            return my_putstr_maj(va_arg(*arg, char const *));
        case 'd':
            return my_put_nbr(va_arg(*arg, int));
        case 'i':
            return my_put_nbr(va_arg(*arg, int));
        case '%':
            return my_putchar_int('%');
        default:
            return dispatch_2(specifier, arg);
    }
}

static void handle_format_char(const char *format, int *i, va_list *arg)
{
    if (format[*i] == '%') {
        (*i)++;
        if (format[*i] == '\0')
            return;
        dispatch(format[*i], arg);
    } else {
        my_putchar(format[*i]);
    }
}

int my_printf(const char *format, ...)
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
