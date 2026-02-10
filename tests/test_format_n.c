/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** test_format_n.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_printf_n, basic_n, .init = redirect_all_std)
{
    int n1 = 0;
    int n2 = 0;

    my_printf("Hello%n World%n!", &n1, &n2);
    cr_assert_eq(n1, 5);
    cr_assert_eq(n2, 11);
}

Test(my_printf_n, n_at_start, .init = redirect_all_std)
{
    int n = 0;

    my_printf("%nHello", &n);
    cr_assert_eq(n, 0);
}

Test(my_printf_n, n_at_end, .init = redirect_all_std)
{
    int n = 0;

    my_printf("Hello%n", &n);
    cr_assert_eq(n, 5);
}

Test(my_printf_n, n_with_other_formats, .init = redirect_all_std)
{
    int n = 0;

    my_printf("%d%n-%s", 42, &n, "test");
    cr_assert_eq(n, 2);
}

Test(my_printf_n, multiple_n, .init = redirect_all_std)
{
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;

    my_printf("A%nBC%nDEF%n", &n1, &n2, &n3);
    cr_assert_eq(n1, 1);
    cr_assert_eq(n2, 3);
    cr_assert_eq(n3, 6);
}

Test(my_printf_n, n_null_pointer, .init = redirect_all_std)
{
    my_printf("Hello%n World", (int *)NULL);
    cr_assert_stdout_eq_str("Hello World");
}
