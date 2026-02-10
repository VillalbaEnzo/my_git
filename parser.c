/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** parser
*/

#include "include/my.h"

// %[flags][width][.precision][length]specifier

static int get_flag_value(char c)
{
    if (c == '-')
        return FLAG_MINUS;
    if (c == '+')
        return FLAG_PLUS;
    if (c == ' ')
        return FLAG_SPACE;
    if (c == '0')
        return FLAG_ZERO;
    if (c == '#')
        return FLAG_HASH;
    return 0;
}

static int parse_flags(const char *format, int *i, format_spec_t *spec)
{
    int count = 0;
    int flag = get_flag_value(format[*i]);

    while (flag) {
        spec->flags |= flag;
        (*i)++;
        count++;
        flag = get_flag_value(format[*i]);
    }
    return count;
}

// Width : number or *
// If *, the width is given as an int argument
static int parse_width(const char *format, int *i,
    format_spec_t *spec, va_list args)
{
    if (format[*i] == '*') {
        spec->width = va_arg(args, int);
        if (spec->width < 0) {
            spec->flags |= FLAG_MINUS;
            spec->width = -spec->width;
        }
        (*i)++;
        return 1;
    } else {
        spec->width = 0;
        while (format[*i] >= '0' && format[*i] <= '9') {
            spec->width = spec->width * 10 + (format[*i] - '0');
            (*i)++;
        }
    }
    return 0;
}

// Precision : .number or .*
// If .*, the precision is given as an int argument
static int parse_precision(const char *format, int *i,
    format_spec_t *spec, va_list args)
{
    if (format[*i] != '.')
        return 0;
    (*i)++;
    spec->has_precision = 1;
    if (format[*i] == '*') {
        spec->precision = va_arg(args, int);
        (*i)++;
        return 1;
    } else {
        spec->precision = 0;
        while (format[*i] >= '0' && format[*i] <= '9') {
            spec->precision = spec->precision * 10 + (format[*i] - '0');
            (*i)++;
        }
    }
    return 1;
}

static int parse_h_length(const char *format, int *i, format_spec_t *spec)
{
    spec->length = 'h';
    (*i)++;
    if (format[*i] != 'h')
        return 1;
    spec->length = 'H';
    (*i)++;
    return 2;
}

static int parse_l_length(const char *format, int *i, format_spec_t *spec)
{
    spec->length = 'l';
    (*i)++;
    if (format[*i] != 'l')
        return 1;
    spec->length = 'L';
    (*i)++;
    return 2;
}

static int parse_single_length(const char *format, int *i, format_spec_t *spec)
{
    if (format[*i] == 'L' || format[*i] == 'j' ||
        format[*i] == 'z' || format[*i] == 't') {
        spec->length = format[*i];
        (*i)++;
        return 1;
    }
    return 0;
}

static int parse_length(const char *format, int *i, format_spec_t *spec)
{
    if (format[*i] == 'h')
        return parse_h_length(format, i, spec);
    if (format[*i] == 'l')
        return parse_l_length(format, i, spec);
    return parse_single_length(format, i, spec);
}

// Main parsing function
int parse_format_spec(const char *format, int *i,
    format_spec_t *spec, va_list args)
{
    int count = 0;

    spec->flags = 0;
    spec->width = 0;
    spec->precision = 0;
    spec->length = 0;
    spec->has_precision = 0;
    count += parse_flags(format, i, spec);
    count += parse_width(format, i, spec, args);
    count += parse_precision(format, i, spec, args);
    count += parse_length(format, i, spec);
    if (format[*i] == '\0')
        return -1;
    spec->specifier = format[*i];
    (*i)++;
    count++;
    return count;
}
