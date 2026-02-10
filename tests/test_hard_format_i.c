/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18 [WSL: Ubuntu-24.04]
** File description:
** test_hard_format_i.c
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

Test(my_printf_hard_integers, zero_flag_ignored_by_precision,
    .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[% 8.5d]", 123);
    my_printf("[%0 8.5d]", 123);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_hard_integers, minus_flag_overrides_zero,
    .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%-10d]", -42);
    my_printf("[%-010d]", -42);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_hard_integers, hash_flag_with_zero_value,
    .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "o:[%o] x:[%x]", 0, 0);
    my_printf("o:[%#o] x:[%#x]", 0, 0);
    cr_assert_stdout_eq_str(expected);
}
