/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** test_format_xX.c
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

Test(my_printf_xX, simple_x, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%x]", 255);
    my_printf("[%x]", 255);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_xX, simple_X, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%X]", 255);
    my_printf("[%X]", 255);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_xX, zero_value, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%x]", 0);
    my_printf("[%x]", 0);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_xX, width, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%10x]", 4779);
    my_printf("[%10x]", 4779);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_xX, left_justify, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%-10X]", 4779);
    my_printf("[%-10X]", 4779);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_xX, zero_padding, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%010x]", 4779);
    my_printf("[%010x]", 4779);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_xX, hash_flag_x, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%#x]", 12345);
    my_printf("[%#x]", 12345);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_xX, hash_flag_X, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%#X]", 12345);
    my_printf("[%#X]", 12345);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_xX, hash_flag_with_zero, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%#x]", 0);
    my_printf("[%#x]", 0);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_xX, precision, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%.10x]", 12345);
    my_printf("[%.10x]", 12345);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_xX, all_flags_complex_x, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%-#15.8x]", 98765);
    my_printf("[%-#15.8x]", 98765);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_xX, hash_zero_width_and_precision, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%#15.8X]", 98765);
    my_printf("[%#015.8X]", 98765);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_xX, length_llx, .init = redirect_all_std)
{
    char expected[256];
    unsigned long long num = 9876543210987654321ULL;
    snprintf(expected, sizeof(expected), "[%-#25.22llx]", num);
    my_printf("[%-#25.22llx]", num);
    cr_assert_stdout_eq_str(expected);
}
