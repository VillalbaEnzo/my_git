/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** test_format_aA.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include "../include/my.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_printf_a, simple_float, .init = redirect_all_std)
{
    char expected[256];

    snprintf(expected, sizeof(expected), "%a", 3.14159);
    my_printf("%a", 3.14159);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_a, zero, .init = redirect_all_std)
{
    char expected[256];

    snprintf(expected, sizeof(expected), "%a", 0.0);
    my_printf("%a", 0.0);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_a, one, .init = redirect_all_std)
{
    char expected[256];

    snprintf(expected, sizeof(expected), "%a", 1.0);
    my_printf("%a", 1.0);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_a, negative, .init = redirect_all_std)
{
    char expected[256];

    snprintf(expected, sizeof(expected), "%a", -2.5);
    my_printf("%a", -2.5);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_a, power_of_two, .init = redirect_all_std)
{
    char expected[256];

    snprintf(expected, sizeof(expected), "%a", 1024.0);
    my_printf("%a", 1024.0);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_a, small_fraction, .init = redirect_all_std)
{
    char expected[256];

    snprintf(expected, sizeof(expected), "%a", 0.5);
    my_printf("%a", 0.5);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_a, infinity, .init = redirect_all_std)
{
    char expected[256];
    double inf = 1.0 / 0.0;

    snprintf(expected, sizeof(expected), "%a", inf);
    my_printf("%a", inf);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_a, negative_infinity, .init = redirect_all_std)
{
    char expected[256];
    double neg_inf = -1.0 / 0.0;

    snprintf(expected, sizeof(expected), "%a", neg_inf);
    my_printf("%a", neg_inf);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_a, nan, .init = redirect_all_std)
{
    char expected[256];
    double nan = 0.0 / 0.0;

    snprintf(expected, sizeof(expected), "%a", nan);
    my_printf("%a", nan);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_A, simple_float_upper, .init = redirect_all_std)
{
    char expected[256];

    snprintf(expected, sizeof(expected), "%A", 3.14159);
    my_printf("%A", 3.14159);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_A, negative_upper, .init = redirect_all_std)
{
    char expected[256];

    snprintf(expected, sizeof(expected), "%A", -2.5);
    my_printf("%A", -2.5);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_A, infinity_upper, .init = redirect_all_std)
{
    char expected[256];
    double inf = 1.0 / 0.0;

    snprintf(expected, sizeof(expected), "%A", inf);
    my_printf("%A", inf);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_A, nan_upper, .init = redirect_all_std)
{
    char expected[256];
    double nan = 0.0 / 0.0;

    snprintf(expected, sizeof(expected), "%A", nan);
    my_printf("%A", nan);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_a, with_plus_flag, .init = redirect_all_std)
{
    char expected[256];

    snprintf(expected, sizeof(expected), "%+a", 3.14);
    my_printf("%+a", 3.14);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_a, with_space_flag, .init = redirect_all_std)
{
    char expected[256];

    snprintf(expected, sizeof(expected), "% a", 3.14);
    my_printf("% a", 3.14);
    cr_assert_stdout_eq_str(expected);
}
