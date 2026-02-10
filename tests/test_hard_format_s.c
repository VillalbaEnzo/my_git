/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18 [WSL: Ubuntu-24.04]
** File description:
** test_hard_format_s.c
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

Test(my_printf_hard_strings, wide_string_precision_cuts_multibyte,
    .init = redirect_all_std)
{
    char expected[256];

    setlocale(LC_ALL, "");
    snprintf(expected, sizeof(expected), "[%.4ls]", L"你好");
    my_printf("[%.4ls]", L"你好");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_hard_strings, null_pointer_with_padding_and_precision,
    .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[          ]");
    my_printf("[%10.3s]", (char *)NULL);
    cr_assert_stdout_eq_str(expected);
}
