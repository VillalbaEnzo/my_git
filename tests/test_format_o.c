/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** test_format_o.c
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

Test(my_printf_o, simple, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%o]", 8);
    my_printf("[%o]", 8);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_o, zero_value, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%o]", 0);
    my_printf("[%o]", 0);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_o, large_number, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%o]", 9999);
    my_printf("[%o]", 9999);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_o, width, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%10o]", 123);
    my_printf("[%10o]", 123);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_o, left_justify, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%-10o]", 123);
    my_printf("[%-10o]", 123);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_o, zero_padding, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%010o]", 123);
    my_printf("[%010o]", 123);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_o, hash_flag, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%#o]", 123);
    my_printf("[%#o]", 123);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_o, hash_flag_with_zero, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%#o]", 0);
    my_printf("[%#o]", 0);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_o, precision, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%.10o]", 123);
    my_printf("[%.10o]", 123);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_o, precision_zero_with_zero_value, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[]");
    my_printf("[%.0o]", 0);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_o, width_precision_and_left_justify, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%-10.5o]", 123);
    my_printf("[%-10.5o]", 123);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_o, all_flags_complex, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%-#15.8o]", 9876);
    my_printf("[%-#15.8o]", 9876);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_o, length_llo, .init = redirect_all_std)
{
    char expected[256];
    unsigned long long num = 18446744073709551615ULL;
    snprintf(expected, sizeof(expected), "[%llo]", num);
    my_printf("[%llo]", num);
    cr_assert_stdout_eq_str(expected);
}
