/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** test_format_p.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_printf_p, simple_pointer, .init = redirect_all_std)
{
    char expected[256];
    int var = 42;
    void *ptr = &var;
    snprintf(expected, sizeof(expected), "[%p]", ptr);
    my_printf("[%p]", ptr);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_p, null_pointer, .init = redirect_all_std)
{
    char expected[256];
    void *ptr = NULL;
    snprintf(expected, sizeof(expected), "[%p]", ptr);
    my_printf("[%p]", ptr);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_p, width_padding, .init = redirect_all_std)
{
    char expected[256];
    int var = 42;
    void *ptr = &var;
    snprintf(expected, sizeof(expected), "[%20p]", ptr);
    my_printf("[%20p]", ptr);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_p, minus_flag, .init = redirect_all_std)
{
    char expected[256];
    int var = 42;
    void *ptr = &var;
    snprintf(expected, sizeof(expected), "[%-20p]", ptr);
    my_printf("[%-20p]", ptr);
    cr_assert_stdout_eq_str(expected);
}
