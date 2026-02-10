/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18 [WSL: Ubuntu-24.04]
** File description:
** float_auto
*/

#include "../include/my.h"

static int count_large_exp(double *abs_val)
{
    int exponent = 0;

    while (*abs_val >= 10.0) {
        *abs_val /= 10.0;
        exponent++;
    }
    return exponent;
}

static int count_small_exp(double *abs_val)
{
    int exponent = 0;

    while (*abs_val < 1.0) {
        *abs_val *= 10.0;
        exponent--;
    }
    return exponent;
}

static int get_exponent_value(double value)
{
    int exponent = 0;
    double abs_val = my_abs_double(value);

    if (abs_val == 0.0)
        return 0;
    if (abs_val >= 10.0)
        exponent = count_large_exp(&abs_val);
    else if (abs_val < 1.0)
        exponent = count_small_exp(&abs_val);
    return exponent;
}

static void set_exp_format(format_spec_t *spec, int precision, int uppercase)
{
    spec->specifier = uppercase ? 'E' : 'e';
    spec->precision = (precision > 0) ? precision - 1 : 0;
    spec->has_precision = 1;
}

static void set_float_format(format_spec_t *spec, int precision,
    int exponent, int uppercase)
{
    spec->specifier = uppercase ? 'F' : 'f';
    spec->precision = (precision > exponent + 1) ?
        precision - exponent - 1 : 0;
    spec->has_precision = 1;
}

int handle_float_auto(format_spec_t *spec, va_list args)
{
    double value = (spec->length == 'L') ?
        (double)va_arg(args, long double) : va_arg(args, double);
    int precision = spec->has_precision ? spec->precision : 6;
    int exponent = get_exponent_value(value);
    int uppercase = (spec->specifier == 'G');
    char original_spec = spec->specifier;

    if (precision == 0)
        precision = 1;
    if (exponent < -4 || exponent >= precision)
        set_exp_format(spec, precision, uppercase);
    else
        set_float_format(spec, precision, exponent, uppercase);
    spec->specifier = original_spec;
    return 0;
}
