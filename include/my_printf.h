/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** my_printf.h
*/

#ifndef MY_PRINTF_H
    #define MY_PRINTF_H

    #include <stdarg.h>

    #define FLAG_MINUS (1 << 0) // -
    #define FLAG_PLUS (1 << 1) // +
    #define FLAG_SPACE (1 << 2) // ' '
    #define FLAG_ZERO (1 << 3) // 0
    #define FLAG_HASH (1 << 4) // #

typedef struct format_spec_s {
    char specifier;
    int flags;
    int width;
    int precision;
    char length;
    int has_precision;
    int chars_written;
} format_spec_t;

int parse_format_spec(const char *format, int *i,
    format_spec_t *spec, va_list args);
int my_printf(const char *format, ...);

#endif /* MY_PRINTF_H */
