/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** test_format_percent.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_printf_percent, simple_percent, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "%%");
    my_printf("%%");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_percent, percent_with_text, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "A percent sign %% is here.");
    my_printf("A percent sign %% is here.");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_percent, multiple_percents, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "100%% of %% signs.");
    my_printf("100%% of %% signs.");
    cr_assert_stdout_eq_str(expected);
}
