/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** hexa.c
*/

#include "../include/my.h"

static int count_hexa_digits(unsigned long long nb)
{
    int count = 0;

    if (nb == 0) {
        return 1;
    }
    while (nb > 0) {
        nb /= 16;
        count++;
    }
    return count;
}

static unsigned long long get_hexa_value(format_spec_t *spec, va_list args)
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

static void adjust_hexa_precision(format_spec_t *spec,
    int *num_len, int *prec_pad, unsigned long long value)
{
    if (spec->has_precision && spec->precision > *num_len)
        *prec_pad = spec->precision - *num_len;
    if (spec->has_precision && spec->precision == 0 && value == 0) {
        *num_len = 0;
    }
}

static void print_right_padding_hexa(format_spec_t *spec,
    unsigned_print_params_t *params, int *count, hexa_flags_t *flags)
{
    if ((spec->flags & FLAG_ZERO) && !spec->has_precision) {
        if (flags->has_prefix)
            *count += my_putstr(flags->is_upper ? "0X" : "0x");
        print_padding('0', params->width_pad, count);
    } else {
        print_padding(' ', params->width_pad, count);
        if (flags->has_prefix)
            *count += my_putstr(flags->is_upper ? "0X" : "0x");
    }
}

static void print_hexa_with_padding(format_spec_t *spec,
    unsigned long long value, int *count, unsigned_print_params_t *params)
{
    hexa_flags_t flags;

    flags.has_prefix = ((spec->flags & FLAG_HASH) && value != 0);
    flags.is_upper = (spec->specifier == 'X');
    if (!(spec->flags & FLAG_MINUS))
        print_right_padding_hexa(spec, params, count, &flags);
    if (spec->flags & FLAG_MINUS) {
        if (flags.has_prefix)
            *count += my_putstr(flags.is_upper ? "0X" : "0x");
    }
    print_padding('0', params->prec_pad, count);
    if (params->num_len > 0)
        *count += my_put_hexa(value, spec);
    if (spec->flags & FLAG_MINUS)
        print_padding(' ', params->width_pad, count);
}

int handle_hexa(format_spec_t *spec, va_list args)
{
    unsigned long long value = get_hexa_value(spec, args);
    int count = 0;
    unsigned_print_params_t params;
    int total_len = 0;
    int prefix_len = 0;

    params.num_len = count_hexa_digits(value);
    params.prec_pad = 0;
    adjust_hexa_precision(spec, &params.num_len, &params.prec_pad, value);
    if ((spec->flags & FLAG_HASH) && value != 0) {
        prefix_len = 2;
    }
    total_len = params.num_len + params.prec_pad + prefix_len;
    params.width_pad = (spec->width > total_len) ? spec->width - total_len : 0;
    print_hexa_with_padding(spec, value, &count, &params);
    return count;
}
