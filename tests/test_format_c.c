/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** test_format_c.c
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

Test(my_printf_c, char_simple, .init = redirect_all_std)
{
    char expected[256] = "";
    snprintf(expected, sizeof(expected), "[%c]", 'A');
    my_printf("[%c]", 'A');
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_c, char_width_padding_right, .init = redirect_all_std)
{
    char expected[256] = "";
    snprintf(expected, sizeof(expected), "[%5c]", 'X');
    my_printf("[%5c]", 'X');
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_c, char_width_padding_left, .init = redirect_all_std)
{
    char expected[256] = "";
    snprintf(expected, sizeof(expected), "[%-5c]", 'Y');
    my_printf("[%-5c]", 'Y');
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_c, char_flag_zero_is_ignored, .init = redirect_all_std)
{
    char expected[256] = "";
    snprintf(expected, sizeof(expected), "[%5c]", 'Z');
    my_printf("[%05c]", 'Z');
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_c, char_flags_plus_space_are_ignored, .init = redirect_all_std)
{
    char expected[256] = "";
    snprintf(expected, sizeof(expected), "[%c] [%c]", 'T', 'T');
    my_printf("[%+c] [% c]", 'T', 'T');
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_c, wchar_simple, .init = redirect_all_std)
{
    char expected[256] = "";
    wchar_t wc = L'€';
    setlocale(LC_ALL, "");
    snprintf(expected, sizeof(expected), "[%lc]", wc);
    my_printf("[%lc]", wc);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_c, wchar_with_padding, .init = redirect_all_std)
{
    wchar_t wc = L'嗨';
    char expected[256] = "";
    setlocale(LC_ALL, "");
    snprintf(expected, sizeof(expected), "[%5lc]", wc);
    my_printf("[%5lc]", wc);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_c, wchar_with_left_padding, .init = redirect_all_std)
{
    wchar_t wc = L'嗨';
    char expected[256] = "";
    setlocale(LC_ALL, "");
    snprintf(expected, sizeof(expected), "[%-5lc]", wc);
    my_printf("[%-5lc]", wc);
    cr_assert_stdout_eq_str(expected);
}
