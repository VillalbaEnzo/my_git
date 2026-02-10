/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18 [WSL: Ubuntu-24.04]
** File description:
** test_hard_format_combi.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>
#include <math.h>
#include "../include/my.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_printf_hard_combinations, kitchen_sink, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected),
        "[%-15.8Lf] [%0*d] [%#llX] [%.*s]",
        (long double)-123.4567890123, 10, 42, ULLONG_MAX, 5, "Truncated");
    my_printf(
        "[%-15.8Lf] [%0*d] [%#llX] [%+.*s]",
        (long double)-123.4567890123, 10, 42, ULLONG_MAX, 5, "Truncated");
    cr_assert_stdout_eq_str(expected);
}
