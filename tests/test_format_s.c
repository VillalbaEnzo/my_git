/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** test_format_s.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <locale.h>
#include <wchar.h>
#include "../include/my.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_printf_s, simple_string, .init = redirect_all_std)
{
    char expected[256] = "";
    snprintf(expected, sizeof(expected), "Hello, World!");
    my_printf("Hello, World!");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_s, empty_string, .init = redirect_all_std)
{
    char expected[256] = "";
    snprintf(expected, sizeof(expected), "Prefix[]Suffix");
    my_printf("Prefix[]Suffix", "");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_s, null_pointer, .init = redirect_all_std)
{
    char expected[256] = "";
    snprintf(expected, sizeof(expected), "(null)");
    my_printf("%s", (char *)NULL);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_s, width_padding, .init = redirect_all_std)
{
    char expected[256] = "";
    snprintf(expected, sizeof(expected), "[%10s]", "test");
    my_printf("[%10s]", "test");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_s, width_and_minus_flag, .init = redirect_all_std)
{
    char expected[256] = "";
    snprintf(expected, sizeof(expected), "[%-10s]", "test");
    my_printf("[%-10s]", "test");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_s, precision_truncates, .init = redirect_all_std)
{
    char expected[256] = "";
    snprintf(expected, sizeof(expected), "[%.5s]", "Hello, World!");
    my_printf("[%.5s]", "Hello, World!");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_s, precision_larger_than_str, .init = redirect_all_std)
{
    char expected[256] = "";
    snprintf(expected, sizeof(expected), "[%.10s]", "Hello");
    my_printf("[%.10s]", "Hello");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_s, width_and_precision, .init = redirect_all_std)
{
    char expected[256] = "";
    snprintf(expected, sizeof(expected), "[%20.5s]", "Hello, World!");
    my_printf("[%20.5s]", "Hello, World!");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_s, width_precision_and_minus, .init = redirect_all_std)
{
    char expected[256] = "";
    snprintf(expected, sizeof(expected), "[%-20.5s]", "Hello, World!");
    my_printf("[%-20.5s]", "Hello, World!");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_s, ls_simple_wide_string, .init = redirect_all_std)
{
    char expected[256] = "";
    setlocale(LC_ALL, "");
    snprintf(expected, sizeof(expected), "[%ls]", L"Hello");
    my_printf("[%ls]", L"Hello");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_s, ls_multibyte_string, .init = redirect_all_std)
{
    char expected[256] = "";
    setlocale(LC_ALL, "");
    snprintf(expected, sizeof(expected), "[%ls]", L"你好, 世界 👋");
    my_printf("[%ls]", L"你好, 世界 👋");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_s, ls_null_pointer, .init = redirect_all_std)
{
    char expected[256] = "";
    setlocale(LC_ALL, "");
    snprintf(expected, sizeof(expected), "(null)");
    my_printf("%ls", (wchar_t *)NULL);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_s, ls_width_padding, .init = redirect_all_std)
{
    char expected[256] = "";
    setlocale(LC_ALL, "");
    snprintf(expected, sizeof(expected), "[%10ls]", L"你好");
    my_printf("[%10ls]", L"你好");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_s, ls_width_and_minus_flag, .init = redirect_all_std)
{
    char expected[256] = "";
    setlocale(LC_ALL, "");
    snprintf(expected, sizeof(expected), "[%-10ls]", L"你好");
    my_printf("[%-10ls]", L"你好");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_s, ls_precision_truncates_bytes, .init = redirect_all_std)
{
    char expected[256] = "";
    setlocale(LC_ALL, "");
    snprintf(expected, sizeof(expected), "[%.3ls]", L"Hello");
    my_printf("[%.3ls]", L"Hello");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_s, ls_width_and_precision, .init = redirect_all_std)
{
    char expected[256] = "";
    setlocale(LC_ALL, "");
    snprintf(expected, sizeof(expected), "[%10.4ls]", L"WideStr");
    my_printf("[%10.4ls]", L"WideStr");
    cr_assert_stdout_eq_str(expected);
}
