/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18 [WSL: Ubuntu-24.04]
** File description:
** float
*/

#include "../include/my.h"

static double get_float_value(format_spec_t *spec, va_list args)
{
    if (spec->length == 'L')
        return (double)va_arg(args, long double);
    return va_arg(args, double);
}

static int count_float_len(double value, int precision, int sign_char)
{
    int len = 0;
    long long int_part = (long long)my_abs_double(value);

    if (sign_char)
        len++;
    if (int_part == 0)
        len = 1;
    while (int_part > 0) {
        len++;
        int_part /= 10;
    }
    if (precision > 0)
        len += precision + 1;
    return len;
}

static void print_float_number(double value, int precision,
    int sign_char, int *count)
{
    if (sign_char)
        *count += my_putchar(sign_char);
    *count += my_put_float(my_abs_double(value), precision);
}

static void handle_left_padding(format_spec_t *spec, int width_pad,
    int *sign_char, int *count)
{
    if ((spec->flags & FLAG_ZERO) && *sign_char) {
        *count += my_putchar(*sign_char);
        *sign_char = 0;
    }
    print_padding((spec->flags & FLAG_ZERO) ? '0' : ' ', width_pad, count);
}

static const char *get_special_str(double value, int uppercase, int sign_char)
{
    if (value != value) {
        if (sign_char == '+')
            return uppercase ? "+NAN" : "+nan";
        return uppercase ? "NAN" : "nan";
    }
    if (value == 1.0 / 0.0) {
        if (sign_char == '+')
            return uppercase ? "+INF" : "+inf";
        if (sign_char == ' ')
            return uppercase ? " INF" : " inf";
        return uppercase ? "INF" : "inf";
    }
    if (value == -1.0 / 0.0)
        return uppercase ? "-INF" : "-inf";
    return NULL;
}

static int handle_special_float(format_spec_t *spec, const char *str, int *cnt)
{
    int len = get_special_float_str_len(str);
    int width_pad = (spec->width > len) ? spec->width - len : 0;

    if (!(spec->flags & FLAG_MINUS))
        print_padding(' ', width_pad, cnt);
    *cnt += my_putstr(str);
    if (spec->flags & FLAG_MINUS)
        print_padding(' ', width_pad, cnt);
    return *cnt;
}

int handle_float(format_spec_t *spec, va_list args)
{
    double value = get_float_value(spec, args);
    int count = 0;
    int precision = spec->has_precision ? spec->precision : 6;
    int uppercase = (spec->specifier == 'F');
    int sign_char;
    int width_pad;
    const char *special_str;

    sign_char = get_sign_char_float(value, spec);
    special_str = get_special_str(value, uppercase, sign_char);
    if (special_str)
        return handle_special_float(spec, special_str, &count);
    width_pad = (spec->width > count_float_len(value, precision, sign_char))
        ? spec->width - count_float_len(value, precision, sign_char) : 0;
    if (!(spec->flags & FLAG_MINUS))
        handle_left_padding(spec, width_pad, &sign_char, &count);
    print_float_number(value, precision, sign_char, &count);
    if (spec->flags & FLAG_MINUS)
        print_padding(' ', width_pad, &count);
    return count;
}
