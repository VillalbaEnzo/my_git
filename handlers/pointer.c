/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18 [WSL: Ubuntu-24.04]
** File description:
** pointer.c
*/

#include "../include/my.h"

static int count_pointer_digits(unsigned long long nb)
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

static void print_right_padding_pointer(format_spec_t *spec,
    unsigned_print_params_t *params, int *count, pointer_flags_t *flags)
{
    if ((spec->flags & FLAG_ZERO) && !spec->has_precision) {
        *count += my_putstr("0x");
        print_padding('0', params->width_pad, count);
    } else {
        print_padding(' ', params->width_pad, count);
        *count += my_putstr("0x");
    }
}

static void print_pointer_with_padding(format_spec_t *spec,
    unsigned long long value, int *count, unsigned_print_params_t *params)
{
    pointer_flags_t flags;

    flags.has_prefix = ((spec->flags & FLAG_HASH) && value != 0);
    if (!(spec->flags & FLAG_MINUS))
        print_right_padding_pointer(spec, params, count, &flags);
    if (spec->flags & FLAG_MINUS) {
        *count += my_putstr("0x");
    }
    print_padding('0', params->prec_pad, count);
    if (params->num_len > 0)
        *count += my_put_hexa(value, spec);
    if (spec->flags & FLAG_MINUS)
        print_padding(' ', params->width_pad, count);
}

static int null_pointer(format_spec_t *spec)
{
    char *nil_str = "(nil)";
    int count = 0;
    int nil_len = 5;
    int width_pad = (spec->width > nil_len) ? spec->width - nil_len : 0;

    if (!(spec->flags & FLAG_MINUS))
        print_padding(' ', width_pad, &count);
    count += my_putstr(nil_str);
    if (spec->flags & FLAG_MINUS)
        print_padding(' ', width_pad, &count);
    return count;
}

int handle_pointer(format_spec_t *spec, va_list args)
{
    void *ptr = va_arg(args, void *);
    unsigned long long value = (unsigned long long)ptr;
    int count = 0;
    unsigned_print_params_t params;
    int total_len = 0;
    int prefix_len = 0;

    if (ptr == NULL)
        return null_pointer(spec);
    params.num_len = count_pointer_digits(value);
    params.prec_pad = 0;
    prefix_len = 2;
    total_len = params.num_len + params.prec_pad + prefix_len;
    params.width_pad = (spec->width > total_len) ? spec->width - total_len : 0;
    print_pointer_with_padding(spec, value, &count, &params);
    return count;
}
