/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18 [WSL: Ubuntu-24.04]
** File description:
** test_hard_format_f.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <math.h>
#include "../include/my.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_printf_hard_floats, special_values_with_padding,
    .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "[%10f] [%-10F] [%+f]",
        INFINITY, -INFINITY, NAN);
    my_printf("[%10f] [%-10F] [%+f]", INFINITY, -INFINITY, NAN);
    cr_assert_stdout_eq_str(expected);
}
