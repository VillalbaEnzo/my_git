/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** test_format_misc.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_printf_misc, no_specifiers, .init = redirect_all_std)
{
    char expected[] = "Hello, this is a simple string.";
    my_printf("Hello, this is a simple string.");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_misc, text_before_and_after, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "Value: -42 is the number.");
    my_printf("Value: %d is the number.", -42);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_misc, multiple_specifiers, .init = redirect_all_std)
{
    char expected[256];
    char *s1 = "one";
    char *s2 = "two";
    snprintf(expected, sizeof(expected), "%s %c %s %d\n", s1, 'A', s2, 99);
    my_printf("%s %c %s %d\n", s1, 'A', s2, 99);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_misc, complex_combination, .init = redirect_all_std)
{
    char expected[256];

    snprintf(expected, sizeof(expected),
        "Hex: [%#08x], Signed: [%+d], String: [%-10.3s]",
        255, 42, "HelloWorld");
    my_printf("Hex: [%#08x], Signed: [%+d], String: [%-10.3s]",
        255, 42, "HelloWorld");
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf_misc, unknown_specifier, .init = redirect_all_std)
{
    char expected[256];
    snprintf(expected, sizeof(expected), "Hello %%y World");
    my_printf("Hello %y World");
    cr_assert_stdout_eq_str(expected);
}
