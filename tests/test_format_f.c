/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18 [WSL: Ubuntu-24.04]
** File description:
** test_format_f.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <math.h>
#include "../include/my.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_printf_f, simple_float, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%f]", 123.456);
    my_printf("[%f]", 123.456);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_f, negative_float, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%f]", -987.654);
    my_printf("[%f]", -987.654);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_f, zero_float, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%f]", 0.0);
    my_printf("[%f]", 0.0);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_f, default_precision_is_six, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%f]", 1.23456789);
    my_printf("[%f]", 1.23456789);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_f, specified_precision, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%.2f]", 123.456);
    my_printf("[%.2f]", 123.456);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_f, precision_zero, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%.0f]", 123.456);
    my_printf("[%.0f]", 123.456);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_f, width_padding, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%15f]", 123.456);
    my_printf("[%15f]", 123.456);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_f, minus_flag_left_justify, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%-15.2f]", 123.45);
    my_printf("[%-15.2f]", 123.45);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_f, zero_flag_padding, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%015f]", 123.456);
    my_printf("[%015f]", 123.456);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_f, zero_flag_with_negative, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%015f]", -123.456);
    my_printf("[%015f]", -123.456);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_f, plus_flag_on_positive, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%+f]", 123.456);
    my_printf("[%+f]", 123.456);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_f, space_flag_on_positive, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[% f]", 123.456);
    my_printf("[% f]", 123.456);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_f, long_double_length, .init = redirect_all_std)
{
    char expected[256];
    long double ld = 123456789.123456789L;
    snprintf(expected, sizeof(expected), "[%Lf]", ld);
    my_printf("[%Lf]", ld);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_f, width_and_precision_combined, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%20.8f]", 123.456789123);
    my_printf("[%20.8f]", 123.456789123);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_f, uppercase_F_specifier, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%F]", 123.456);
    my_printf("[%F]", 123.456);
    cr_assert_stdout_eq_str(expected);
}
