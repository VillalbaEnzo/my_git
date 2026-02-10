/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** hexa_float.c
*/

#include "../include/my.h"

static void extract_double_parts(double value, unsigned long long *mantissa,
    int *exponent, int *sign)
{
    unsigned long long bits = *(unsigned long long *)&value;

    *sign = (bits >> 63) & 1;
    *exponent = ((bits >> 52) & 0x7FF) - 1023;
    *mantissa = bits & 0xFFFFFFFFFFFFFULL;
    if (*exponent != -1023) {
        *mantissa |= (1ULL << 52);
    } else {
        if (*mantissa == 0)
            *exponent = 0;
        else
            *exponent = -1022;
    }
}

static int count_trailing_zeros(unsigned long long mantissa)
{
    int zeros = 0;

    if (mantissa == 0)
        return 13;
    while ((mantissa & 0xF) == 0) {
        zeros++;
        mantissa >>= 4;
    }
    return zeros;
}

static int print_hexa_mantissa(unsigned long long mantissa,
    int precision, int uppercase, int has_precision)
{
    char hex_digits[] = "0123456789abcdef";
    char hex_digits_upper[] = "0123456789ABCDEF";
    char *digits = uppercase ? hex_digits_upper : hex_digits;
    int count = 0;
    int digit = (mantissa >> 52) & 0xF;
    int trailing_zeros = count_trailing_zeros(mantissa);
    int digits_to_print = has_precision ? precision : (13 - trailing_zeros);

    count += my_putchar(digits[digit]);
    if (digits_to_print == 0)
        return count;
    count += my_putchar('.');
    for (int i = 0; i < digits_to_print; i++) {
        mantissa <<= 4;
        digit = (mantissa >> 52) & 0xF;
        count += my_putchar(digits[digit]);
    }
    return count;
}

static int print_hexa_exponent(int exponent, int uppercase)
{
    int count = 0;
    char sign = exponent < 0 ? '-' : '+';

    count += my_putchar(uppercase ? 'P' : 'p');
    count += my_putchar(sign);
    if (exponent < 0)
        exponent = -exponent;
    count += my_put_nbr(exponent);
    return count;
}

static int handle_hexa_float_special(double value, int uppercase, int *count)
{
    if (value != value) {
        *count += uppercase ? my_putstr("NAN") : my_putstr("nan");
        return 1;
    }
    if (value == 1.0 / 0.0) {
        *count += uppercase ? my_putstr("INF") : my_putstr("inf");
        return 1;
    }
    if (value == -1.0 / 0.0) {
        *count += my_putchar('-');
        *count += uppercase ? my_putstr("INF") : my_putstr("inf");
        return 1;
    }
    return 0;
}

static int print_sign_prefix(int sign, format_spec_t *spec)
{
    if (sign)
        return my_putchar('-');
    if (spec->flags & FLAG_PLUS)
        return my_putchar('+');
    if (spec->flags & FLAG_SPACE)
        return my_putchar(' ');
    return 0;
}

static int print_hexa_float_value(double value, format_spec_t *spec)
{
    unsigned long long mantissa;
    int exponent;
    int sign;
    int count = 0;

    extract_double_parts(value, &mantissa, &exponent, &sign);
    count += print_sign_prefix(sign, spec);
    count += my_putstr(spec->specifier == 'A' ? "0X" : "0x");
    count += print_hexa_mantissa(mantissa, spec->precision,
        spec->specifier == 'A', spec->has_precision);
    count += print_hexa_exponent(exponent, spec->specifier == 'A');
    return count;
}

int handle_hexa_float(format_spec_t *spec, va_list args)
{
    double value = va_arg(args, double);
    int count = 0;

    if (handle_hexa_float_special(value, spec->specifier == 'A', &count))
        return count;
    return print_hexa_float_value(value, spec);
}
