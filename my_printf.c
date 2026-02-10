/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** my_printf.c
*/

#include "include/my.h"

static int is_known_specifier(char c)
{
    const char *known_specifiers = "diucsFfeEgGoxXpnaA";

    for (int i = 0; known_specifiers[i]; i++) {
        if (c == known_specifiers[i]) {
            return 1;
        }
    }
    return 0;
}

static int process_percent(const char *format, int *i,
    format_spec_t *spec, va_list args)
{
    int start_index = *i;

    (*i)++;
    if (format[*i] == '%') {
        (*i)++;
        return my_putchar('%');
    }
    parse_format_spec(format, i, spec, args);
    if (spec->specifier != '\0' && is_known_specifier(spec->specifier))
        return handle_conversion(spec, args);
    return my_putnstr(&format[start_index], *i - start_index);
}

int my_printf(const char *format, ...)
{
    va_list args;
    int i = 0;
    int count = 0;
    format_spec_t spec;

    va_start(args, format);
    while (format[i]) {
        if (format[i] == '%') {
            spec.chars_written = count;
            count += process_percent(format, &i, &spec, args);
        } else {
            count += my_putchar(format[i]);
            i++;
        }
    }
    va_end(args);
    return count;
}
