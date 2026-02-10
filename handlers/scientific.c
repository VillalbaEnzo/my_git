/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18 [WSL: Ubuntu-24.04]
** File description:
** scientific
*/

#include "../include/my.h"

static int normalize_large_value(double *abs_val)
{
    int exponent = 0;

    while (*abs_val >= 10.0) {
        *abs_val /= 10.0;
        exponent++;
    }
    return exponent;
}

static int normalize_small_value(double *abs_val)
{
    int exponent = 0;

    while (*abs_val < 1.0) {
        *abs_val *= 10.0;
        exponent--;
    }
    return exponent;
}

static int get_exponent(double *value)
{
    int exponent = 0;
    double abs_val = my_abs_double(*value);

    if (abs_val == 0.0)
        return 0;
    if (abs_val >= 10.0)
        exponent = normalize_large_value(&abs_val);
    else if (abs_val < 1.0)
        exponent = normalize_small_value(&abs_val);
    *value = (*value < 0) ? -abs_val : abs_val;
    return exponent;
}

static void print_exponent(int exponent, int uppercase, int *count)
{
    *count += my_putchar(uppercase ? 'E' : 'e');
    *count += my_putchar((exponent >= 0) ? '+' : '-');
    if (exponent < 0)
        exponent = -exponent;
    if (exponent < 10)
        *count += my_putchar('0');
    if (exponent == 0)
        *count += my_putchar('0');
    else {
        if (exponent >= 10)
            *count += my_putchar((exponent / 10) + '0');
        *count += my_putchar((exponent % 10) + '0');
    }
}

static void handle_sci_left_pad(format_spec_t *spec, int width_pad,
    int *sign_char, int *count)
{
    if ((spec->flags & FLAG_ZERO) && *sign_char) {
        *count += my_putchar(*sign_char);
        *sign_char = 0;
    }
    print_padding((spec->flags & FLAG_ZERO) ? '0' : ' ', width_pad, count);
}

static int calc_sci_total_len(int sign_char, int precision)
{
    return (sign_char ? 1 : 0) + 1 + (precision > 0 ? precision + 1 : 0) + 4;
}

static void print_sci_number(sci_print_params_t *params,
    int sign_char, int *count)
{
    if (sign_char)
        *count += my_putchar(sign_char);
    *count += my_put_float(my_abs_double(params->value), params->precision);
    print_exponent(params->exponent, params->uppercase, count);
}

static void print_sci_final(format_spec_t *spec, sci_print_params_t *params,
    sci_format_ctx_t *ctx, int *count)
{
    if (!(spec->flags & FLAG_MINUS))
        handle_sci_left_pad(spec, ctx->width_pad, &ctx->sign_char, count);
    print_sci_number(params, ctx->sign_char, count);
    if (spec->flags & FLAG_MINUS)
        print_padding(' ', ctx->width_pad, count);
}

int handle_scientific(format_spec_t *spec, va_list args)
{
    sci_print_params_t params;
    sci_format_ctx_t ctx;
    int count = 0;

    params.value = (spec->length == 'L') ?
        (double)va_arg(args, long double) : va_arg(args, double);
    params.precision = spec->has_precision ? spec->precision : 6;
    params.uppercase = (spec->specifier == 'E');
    if (print_special_float_value(params.value, params.uppercase, &count))
        return count;
    ctx.sign_char = get_sign_char_float(params.value, spec);
    params.exponent = get_exponent(&params.value);
    ctx.width_pad = (spec->width > calc_sci_total_len(ctx.sign_char,
            params.precision)) ? spec->width -
        calc_sci_total_len(ctx.sign_char, params.precision) : 0;
    print_sci_final(spec, &params, &ctx, &count);
    return count;
}
