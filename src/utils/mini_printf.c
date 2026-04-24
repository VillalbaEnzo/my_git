/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** mini_printf.c
*/

#include <stdlib.h>
#include <stdarg.h>
#include "utils.h"

void char_cases(const char *format, va_list *args, int *cnt, int fd)
{
    switch (*(format + 1)) {
        case 's':
            *cnt += my_putstr(va_arg(*args, char *), fd);
            break;
        case 'c':
            my_putchar((char) va_arg(*args, int), fd);
            *cnt += 1;
            break;
        case '%':
            my_putchar('%', fd);
            *cnt += 1;
            break;
    }
}

void integer_cases(const char *format, va_list *args, int *cnt, int fd)
{
    switch (*(format + 1)) {
        case 'd':
        case 'i':
            my_put_nbr(va_arg(*args, long), cnt, fd);
            break;
    }
}

int mini_printf(int fd, const char *format, ...)
{
    va_list args;
    int cnt = 0;

    if (format == NULL)
        return 84;
    va_start(args, format);
    while (*format != '\0') {
        if (*format == '%') {
            char_cases(format, &args, &cnt, fd);
            integer_cases(format, &args, &cnt, fd);
            format++;
        } else {
            my_putchar(*format, fd);
            cnt++;
        }
        format++;
    }
    va_end(args);
    return cnt;
}
