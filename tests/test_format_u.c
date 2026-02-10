/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** test_format_u.c
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

Test(my_printf_u, simple, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%u]", 123);
    my_printf("[%u]", 123);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_u, zero, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%u]", 0);
    my_printf("[%u]", 0);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_u, uint_max, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%u]", UINT_MAX);
    my_printf("[%u]", UINT_MAX);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_u, width_padding, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%10u]", 42);
    my_printf("[%10u]", 42);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_u, minus_flag, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%-10u]", 42);
    my_printf("[%-10u]", 42);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_u, zero_flag, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%010u]", 42);
    my_printf("[%010u]", 42);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_u, precision, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%.5u]", 42);
    my_printf("[%.5u]", 42);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_u, width_and_precision, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%10.5u]", 42);
    my_printf("[%10.5u]", 42);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_u, length_lu, .init = redirect_all_std)
{
    char expected[256];
    unsigned long num = ULONG_MAX;
    snprintf(expected, sizeof(expected), "[%lu]", num);
    my_printf("[%lu]", num);
    cr_assert_stdout_eq_str(expected);
}
