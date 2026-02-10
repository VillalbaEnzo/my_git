/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** octal.c
*/

#include "../include/my.h"

static int count_octal_digits(unsigned long long nb)
{
    int count = 0;

    if (nb == 0) {
        return 1;
    }
    while (nb > 0) {
        nb /= 8;
        count++;
    }
    return count;
}

static unsigned long long get_octal_value(format_spec_t *spec, va_list args)
{
    if (spec->length == 'H')
        return (unsigned char)va_arg(args, unsigned int);
    if (spec->length == 'h')
        return (unsigned short)va_arg(args, unsigned int);
    if (spec->length == 'l')
        return va_arg(args, unsigned long);
    if (spec->length == 'L')
        return va_arg(args, unsigned long long);
    if (spec->length == 'j')
        return va_arg(args, uintmax_t);
    if (spec->length == 'z')
        return va_arg(args, size_t);
    if (spec->length == 't')
        return va_arg(args, ptrdiff_t);
    return va_arg(args, unsigned int);
}

static void print_left_padding(format_spec_t *spec, int width_pad, int *count)
{
    if (spec->flags & FLAG_ZERO && !(spec->flags & FLAG_MINUS) &&
        !spec->has_precision) {
        print_padding('0', width_pad, count);
    } else {
        print_padding(' ', width_pad, count);
    }
}

static void adjust_octal_precision(format_spec_t *spec,
    int *num_len, int *prec_pad, unsigned long long value)
{
    if (spec->has_precision && spec->precision > *num_len)
        *prec_pad = spec->precision - *num_len;
    if (spec->has_precision && spec->precision == 0 && value == 0) {
        if (!(spec->flags & FLAG_HASH))
            *num_len = 0;
    }
}

static void print_octal_with_padding(format_spec_t *spec,
    unsigned long long value, int *count, unsigned_print_params_t *params)
{
    if (!(spec->flags & FLAG_MINUS))
        print_left_padding(spec, params->width_pad, count);
    if ((spec->flags & FLAG_HASH) && value != 0 && params->prec_pad == 0)
        *count += my_putchar('0');
    print_padding('0', params->prec_pad, count);
    if (params->num_len > 0)
        *count += my_put_nbr_octal(value);
    if (spec->flags & FLAG_MINUS)
        print_padding(' ', params->width_pad, count);
}

int handle_octal(format_spec_t *spec, va_list args)
{
    unsigned long long value = get_octal_value(spec, args);
    int count = 0;
    unsigned_print_params_t params;
    int total_len;

    params.num_len = count_octal_digits(value);
    params.prec_pad = 0;
    adjust_octal_precision(spec, &params.num_len, &params.prec_pad, value);
    total_len = params.num_len + params.prec_pad;
    if ((spec->flags & FLAG_HASH) && value != 0 && params.prec_pad == 0)
        total_len++;
    params.width_pad = (spec->width > total_len) ? spec->width - total_len : 0;
    print_octal_with_padding(spec, value, &count, &params);
    return count;
}
