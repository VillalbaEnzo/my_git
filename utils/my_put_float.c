/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** my_put_float.c
*/

#include "../include/my.h"

static void print_float_integer_part(long long int_part, int *count)
{
    if (int_part < 0) {
        *count += my_putchar('-');
        int_part = -int_part;
    }
    if (int_part / 10 != 0)
        print_float_integer_part(int_part / 10, count);
    *count += my_putchar((int_part % 10) + '0');
}

static void print_float_decimal_part(double frac_part,
    int precision, int *count)
{
    int digit = 0;

    for (int i = 0; i < precision; i++) {
        frac_part *= 10;
        digit = (int)frac_part;
        *count += my_putchar(digit + '0');
        frac_part -= digit;
    }
}

static int handle_special_values(double value)
{
    int count = 0;

    if (value != value)
        return my_putstr("nan");
    if (value == 1.0 / 0.0)
        return my_putstr("inf");
    if (value == -1.0 / 0.0)
        return my_putstr("-inf");
    return count;
}

static void round_and_adjust(double *frac_part, long long *int_part,
    double value, int precision)
{
    double rounding_factor = 0.5 * my_power(10, -precision);

    *frac_part += rounding_factor;
    if (*frac_part >= 1.0) {
        *int_part += (value >= 0) ? 1 : -1;
        *frac_part -= 1.0;
    }
}

int my_put_float(double value, int precision)
{
    int count = 0;
    long long int_part;
    double frac_part;

    count = handle_special_values(value);
    if (count > 0)
        return count;
    int_part = (long long)value;
    frac_part = value - (double)int_part;
    if (frac_part < 0)
        frac_part = -frac_part;
    round_and_adjust(&frac_part, &int_part, value, precision);
    print_float_integer_part(int_part, &count);
    if (precision > 0) {
        count += my_putchar('.');
        print_float_decimal_part(frac_part, precision, &count);
    }
    return count;
}
