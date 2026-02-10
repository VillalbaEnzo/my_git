/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** int.c
*/

#include "../include/my.h"


static long long get_int_value(format_spec_t *spec, va_list args)
{
    if (spec->length == 'H')
        return (signed char)va_arg(args, int);
    if (spec->length == 'h')
        return (short)va_arg(args, int);
    if (spec->length == 'l')
        return va_arg(args, long);
    if (spec->length == 'L')
        return va_arg(args, long long);
    if (spec->length == 'j')
        return va_arg(args, intmax_t);
    if (spec->length == 'z')
        return va_arg(args, ssize_t);
    if (spec->length == 't')
        return va_arg(args, ptrdiff_t);
    return va_arg(args, int);
}

static void print_left_padding(format_spec_t *spec, int width_pad,
    int sign_char, int *count)
{
    int use_zero = spec->flags & FLAG_ZERO && !(spec->flags & FLAG_MINUS)
        && !spec->has_precision;

    if (use_zero) {
        if (sign_char)
            *count += my_putchar(sign_char);
        print_padding('0', width_pad, count);
    } else {
        print_padding(' ', width_pad, count);
        if (sign_char)
            *count += my_putchar(sign_char);
    }
}

static void print_number(long long value, int *count)
{
    if (value == 0) {
        *count += my_putchar('0');
    } else {
        print_number_signed((value < 0) ? -value : value, count);
    }
}

static void adjust_precision(format_spec_t *spec, int *num_len,
    int *prec_pad, long long value)
{
    if (spec->has_precision && spec->precision > *num_len)
        *prec_pad = spec->precision - *num_len;
    if (spec->has_precision && spec->precision == 0 && value == 0)
        *num_len = 0;
}

static void print_int_with_padding(format_spec_t *spec, long long value,
    int *count, int_print_params_t *params)
{
    if (!(spec->flags & FLAG_MINUS))
        print_left_padding(spec, params->width_pad, params->sign_char, count);
    else if (params->sign_char)
        *count += my_putchar(params->sign_char);
    print_padding('0', params->prec_pad, count);
    if (params->num_len > 0)
        print_number(value, count);
    if (spec->flags & FLAG_MINUS)
        print_padding(' ', params->width_pad, count);
}

int handle_int(format_spec_t *spec, va_list args)
{
    long long value = get_int_value(spec, args);
    int count = 0;
    int_print_params_t params;
    int total_len = 0;

    params.num_len = count_digits_signed(value);
    params.prec_pad = 0;
    params.sign_char = get_sign_char_int(value, spec);
    adjust_precision(spec, &params.num_len, &params.prec_pad, value);
    total_len = params.num_len + params.prec_pad +
        (params.sign_char ? 1 : 0);
    params.width_pad = (spec->width > total_len) ? spec->width - total_len : 0;
    print_int_with_padding(spec, value, &count, &params);
    return count;
}
