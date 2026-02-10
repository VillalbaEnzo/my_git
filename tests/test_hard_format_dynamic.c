/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18 [WSL: Ubuntu-24.04]
** File description:
** test_hard_format_dynamic.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_printf_hard_dynamic, width_and_precision, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%*.*s]", 10, 5, "HelloWorld");
    my_printf("[%*.*s]", 10, 5, "HelloWorld");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_hard_dynamic, negative_width_as_minus_flag,
    .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%-10d]", 123);
    my_printf("[%*d]", -10, 123);
    cr_assert_stdout_eq_str(expected);
}
