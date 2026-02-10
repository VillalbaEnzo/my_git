/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** test_format_di.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>
#include "../include/my.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_printf_di, simple_positive, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%d]", 123);
    my_printf("[%d]", 123);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, simple_negative, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%i]", -456);
    my_printf("[%i]", -456);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, simple_zero, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%d]", 0);
    my_printf("[%d]", 0);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, int_max, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%i]", INT_MAX);
    my_printf("[%i]", INT_MAX);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, int_min, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%i]", INT_MIN);
    my_printf("[%i]", INT_MIN);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, basic_width_right_justify, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%4i]", 12);
    my_printf("[%4i]", 12);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, flag_minus_left_justify, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%-4i]", 12);
    my_printf("[%-4i]", 12);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, flag_zero_padding, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%04i]", 12);
    my_printf("[%04i]", 12);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, negative_with_zero_flag, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%05i]", -12);
    my_printf("[%05i]", -12);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, flag_plus_on_positive, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%+i]", 42);
    my_printf("[%+i]", 42);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, flag_plus_on_negative, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%+i]", -42);
    my_printf("[%+i]", -42);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, flag_space_on_positive, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[% i]", 42);
    my_printf("[% i]", 42);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, flag_space_on_negative, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[% i]", -42);
    my_printf("[% i]", -42);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, flag_minus_overrides_zero_flag, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%-4i]", 12);
    my_printf("[%-04i]", 12);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, flag_plus_overrides_space_flag, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%+i]", 42);
    my_printf("[%+ i]", 42);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, flags_zero_and_plus_with_padding, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%0+6i]", 42);
    my_printf("[%0+6i]", 42);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, precision_pads_with_zeros, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%.5i]", 123);
    my_printf("[%.5i]", 123);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, precision_does_not_truncate_number, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%.2i]", 12345);
    my_printf("[%.2i]", 12345);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, edge_case_zero_with_zero_precision, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[]");
    my_printf("[%.0i]", 0);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, width_and_precision, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%8.5i]", 123);
    my_printf("[%8.5i]", 123);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, width_precision_and_minus_flag, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%-8.5i]", 123);
    my_printf("[%-8.5i]", 123);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, negative_with_width_and_precision, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%8.5i]", -12);
    my_printf("[%8.5i]", -12);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, precision_overrides_zero_flag, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%8.5i]", 123);
    my_printf("[%08.5i]", 123);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_di, edge_case_zero_with_zero_precision_and_width,
    .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%5.0i]", 0);
    my_printf("[%5.0i]", 0);
    cr_assert_stdout_eq_str(expected);
}
